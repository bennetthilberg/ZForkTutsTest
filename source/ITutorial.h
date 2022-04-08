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
        UI::Button ok_but;
        UI::Button start_but;

    public:
        static void PrintComplete() { std::cout << "Tutorial Complete!" << std::endl; }

        ITutorial(UI::Document animation, UI::Document settings, UI::Document explanation, UI::Document learnmore, UI::Document buttons, UI::Canvas mycanvas): doc("emp_base"), my_button([](){}, "Start Tutorial"), ok_but([](){}, "OK"){
            doc << my_button;
            my_button.SetCSS("position", "relative");
            ok_but.SetCSS("position", "relative");

            /* State declarations */
            tut.AddState("first_state");
            tut.AddState("second_state");
            tut.AddState("third_state");
            tut.AddState("fourth_state");
            tut.AddState("fifth_state");
            tut.AddState("sixth_state");
            tut.AddState("seventh_state");
            tut.AddState("eighth_state");
            tut.AddState("end_state", &PrintComplete);
        }

        void startTut(UI::Document animation, UI::Document settings, UI::Document explanation, UI::Document learnmore, UI::Document buttons, UI::Canvas mycanvas) {
            start_but = buttons.Button("toggle");

            start_but.SetCSS("position", "relative");
            start_but.SetCSS("z-index", "11");
            ok_but.SetCSS("left", "0.7vw");

            /* Transitions */
            tut.AddEventListenerTrigger("first_state", "second_state", my_button, "click", "click_trigger");
            tut.AddEventListenerTrigger("second_state", "third_state", ok_but, "click", "click_ok");
            tut.AddExistingTrigger("third_state", "fourth_state", "click_ok");
            tut.AddExistingTrigger("fourth_state", "fifth_state", "click_ok");
            tut.AddExistingTrigger("fifth_state", "sixth_state", "click_ok");
            tut.AddExistingTrigger("sixth_state", "seventh_state", "click_ok");
            tut.AddExistingTrigger("seventh_state", "eighth_state", "click_ok");
            tut.AddExistingTrigger("eighth_state", "end_state", "click_ok");
            
            /* Effects */
            // First state: no effects
            // Second state: gray overlay spotlight: animation, popover
            tut.AddOverlayEffect("second_state", buttons, animation, "black", 0.8, 10, true);
            tut.AddPopoverEffect("second_state", buttons, "This is a walk through of the UI", ok_but, "15vh", "-1vw");
            tut.AddPopoverEffect("second_state", buttons, "Click it to start the experiement", ok_but, "-0.5vh", "-2vw");
            // Third state: 
            tut.AddOverlayEffect("third_state", buttons, animation, "yellow", 0.8, 10, true);
            // Fourth state: 
            tut.AddOverlayEffect("fourth_state", buttons, animation, "yellow", 0.8, 10, true);
            // Fifth state: 
            tut.AddOverlayEffect("fifth_state", buttons, animation, "yellow", 0.8, 10, true);
            // Sixth state: 
            tut.AddOverlayEffect("sixth_state", buttons, animation, "yellow", 0.8, 10, true);
            // Seventh state: 
            tut.AddOverlayEffect("seventh_state", buttons, animation, "yellow", 0.8, 10, true);
            // Eighth state: 
            tut.AddOverlayEffect("eighth_state", buttons, animation, "yellow", 0.8, 10, true);


            animation.SetCSS("position", "relative");
            animation.SetCSS("z-index", "12");
            tut.StartAtState("first_state");
                

            }
};
#endif