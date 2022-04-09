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

            /* Add all states */
            tut.AddState("first_state");
            tut.AddState("second_state");
            tut.AddState("third_state");
            tut.AddState("fourth_state", &PrintComplete);
            tut.AddOverlayEffect("second_state", buttons, "black", 0.8, 10, true);
            tut.AddOverlayEffect("third_state", buttons, "yellow", 0.8, 10, true);

            /* Transitions */
            tut.AddEventListenerTrigger("first_state", "second_state", my_button, "click", "click_trigger");
            tut.AddEventListenerTrigger("second_state", "third_state", ok_but, "click_okay", "click_ok");
            tut.AddExistingTrigger("third_state", "fourth_state", "click_ok");

            //tut.AddExistingTrigger("second_state", "third_state", "click_trigger");
            //tut.AddEventListenerTrigger("third_state", "end_state", ok_but, "click", "click_ok");
        }

        void startTut(UI::Document animation, UI::Document settings, UI::Document explanation, UI::Document learnmore, UI::Document buttons, UI::Canvas mycanvas) {
            start_but = buttons.Button("toggle");
    
            start_but.SetCSS("position", "relative");
            start_but.SetCSS("z-index", "11");
            ok_but.SetCSS("left", "0.7vw");

            animation.SetCSS("position", "relative");
            animation.SetCSS("z-index", "12");

            
    
            
            /* Popovers */
            tut.AddPopoverEffect("second_state", buttons, "This is a walk through of the UI", ok_but, "15vh", "-1vw");
            tut.AddPopoverEffect("second_state", buttons, "Click it to start the experiement", ok_but, "-0.5vh", "-2vw");




            tut.StartAtState("first_state");
                

            }
};
#endif