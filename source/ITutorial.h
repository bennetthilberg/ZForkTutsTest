#ifndef ITUTORIAL_H
#define ITUTORIAL_H
#include "../Empirical/include/emp/web/KeypressManager.hpp"
#include "../Empirical/include/emp/web/Tutorial.h"
#include <iostream>
#include "default_mode/SymWorld.h"
#include "../Empirical/include/emp/web/Document.hpp"
#include "../Empirical/include/emp/web/Button.hpp"
#include "../Empirical/include/emp/web/Canvas.hpp"
#include "../Empirical/include/emp/web/web.hpp"

namespace UI = emp::web;
class ITutorial {
    private:
        UI::Document doc;
        UI::Button my_button;
        Tutorial tut;

    public:
        static void PrintComplete() { std::cout << "Tutorial Complete!" << std::endl; }

        ITutorial(UI::Document animation, UI::Document settings, UI::Document explanation, UI::Document learnmore, UI::Document buttons, UI::Canvas mycanvas): doc("emp_base"), my_button([](){}, "Start Tutorial"){
            
            doc << my_button;
            my_button.SetCSS("position", "relative");

            tut.AddState("first_state");
            tut.AddState("second_state");
            tut.AddState("end_state", &PrintComplete);
            tut.AddEventListenerTrigger("first_state", "second_state", my_button, "click");
            tut.AddEventListenerTrigger("second_state", "end_state", my_button, "click");
            // tut.AddManualTrigger("second_state", "end_state", "enter_input_trigger");

            tut.AddOverlayEffect("first_state", buttons, "black", 0.5, -1, true);
            tut.AddOverlayEffect("second_state", buttons, "black", 0.5, -1, true);
            tut.AddOverlayEffect("end_state", buttons, "black", 0.5,-1, true);
            // tut.AddCSSEffect("first_state", my_button, "z-index", "50000");

            tut.AddPopoverEffect("second_state", buttons, "This is a pop over!!!!");

            // buttons.Button("toggle").SetCSS("position", "relative");
            // buttons.Button("toggle").SetCSS("z-index", "1");
            // my_button.SetCSS("z-index", "2");
            tut.StartAtState("first_state");

            
        }

        void startTut(UI::Document animation, UI::Document settings, UI::Document explanation, UI::Document learnmore, UI::Document buttons, UI::Canvas mycanvas) {
            // tut.AddState("first_state");
            // tut.AddState("second_state");
            // tut.AddState("end_state", &PrintComplete);
            // tut.AddEventListenerTrigger("first_state", "second_state", my_button, "click");
            // // tut.AddManualTrigger("second_state", "end_state", "enter_input_trigger");

            // tut.AddOverlayEffect("first_state", buttons, "black", 0.5, 3, true);
            // tut.AddOverlayEffect("second_state", buttons, "black", 0.5, 3, true);
            // // tut.AddCSSEffect("first_state", my_button, "z-index", "50000");

            // // tut.AddOverlayEffect("second_state", buttons, "green", 0.5, 1000, true);
            // // tut.AddPopoverEffect("second_state", buttons, "This is a pop over!!!!");

            buttons.Button("toggle").SetCSS("position", "relative");
            buttons.Button("toggle").SetCSS("z-index", "2");
            // // my_button.SetCSS("z-index", "2");
            // tut.StartAtState("first_state");
        }
};
#endif