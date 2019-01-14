#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <gf/Action.h>
#include <gf/Clock.h>
#include <gf/Color.h>
#include <gf/EntityContainer.h>
#include <gf/Event.h>
#include <gf/Id.h>
#include <gf/Curves.h>
#include <gf/RenderWindow.h>
#include <gf/Vector.h>
#include <gf/ViewContainer.h>
#include <gf/Views.h>
#include <gf/Window.h>

int main() {
    gf::Color4f line_color{0.0f, 0.0f, 0.0f, 1.0f};
    gf::Vector2f turtle_pos{0.0f, 0.0f};

    std::vector<gf::Line> lines{};
    std::string line_text{};
    while (std::getline(std::cin, line_text)) {
        std::istringstream line_stream{line_text};
        std::string word{};
        line_stream >> word;

        using namespace gf::literals;

        switch (gf::hash(word)) {
        case "Color"_id: {
            line_stream >> line_color.r;
            line_stream >> line_color.g;
            line_stream >> line_color.b;
        } break;
        
        case "LineTo"_id: {
            gf::Vector2f dest_pos{0.0f, 0.0f};
            line_stream >> dest_pos.x;
            line_stream >> dest_pos.y;
            lines.emplace_back(turtle_pos, dest_pos);
            lines.back().setColor(line_color);
            lines.back().setWidth(5.0f);
            turtle_pos = std::move(dest_pos);
        } break;

        case "MoveTo"_id: {
            line_stream >> turtle_pos.x;
            line_stream >> turtle_pos.y;
        } break;

        default: {
            std::cerr << "Input syntax error" << std::endl;
            return 0;
        }
        }
    }

    static constexpr gf::Vector2u ScreenSize(500, 500);
    static constexpr gf::Vector2f ViewSize(1000.0f, 1000.0f);
    static constexpr gf::Vector2f ViewCenter(0.0f, 0.0f);

    // initialization
    gf::Window window("Insturtle Viewer", ScreenSize);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    gf::RenderWindow renderer(window);

    // views
    gf::ViewContainer views;
    gf::ExtendView mainView(ViewCenter, ViewSize);
    views.addView(mainView);

    views.setInitialScreenSize(ScreenSize);

    // actions
    gf::ActionContainer actions;

    gf::Action closeWindowAction("Close window");
    closeWindowAction.addCloseControl();
    closeWindowAction.addKeycodeKeyControl(gf::Keycode::Escape);
    actions.addAction(closeWindowAction);

    gf::Action fullscreenAction("Fullscreen");
    fullscreenAction.addKeycodeKeyControl(gf::Keycode::F);
    actions.addAction(fullscreenAction);

    gf::Action incThickAction("Increase thickness");
    incThickAction.addKeycodeKeyControl(gf::Keycode::Up);
    actions.addAction(incThickAction);

    gf::Action decThickAction("Decrease thickness");
    decThickAction.addKeycodeKeyControl(gf::Keycode::Down);
    actions.addAction(decThickAction);

    // game loop
    renderer.clear(gf::Color::White);
    gf::Clock clock;
    while (window.isOpen()) {
        // 1. input
        gf::Event event;
        while (window.pollEvent(event)) {
            actions.processEvent(event);
            views.processEvent(event);
        }

        if (closeWindowAction.isActive()) {
            window.close();
        }

        if (fullscreenAction.isActive()) {
            window.toggleFullscreen();
        }

        if (incThickAction.isActive()) {
            for (auto& line : lines) {
                line.setWidth(line.getWidth() + 0.2f);
            }
        }

        if (decThickAction.isActive()) {
            for (auto& line : lines) {
                if (line.getWidth() > 1.1f) {
                    line.setWidth(line.getWidth() - 0.2f);
                }
            }
        }

        // 3. draw
        renderer.clear();
        renderer.setView(mainView);

        for (auto& line : lines) {
            renderer.draw(line);
        }

        renderer.display();
        actions.reset();
    }
    return 0;
}
