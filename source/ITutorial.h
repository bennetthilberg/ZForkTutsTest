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
        bool started = false;

    public:
        static void PrintComplete() { std::cout << "Tutorial Complete!" << std::endl; }

        ITutorial(UI::Document animation, UI::Document settings, UI::Document explanation, UI::Document learnmore, UI::Document buttons, UI::Canvas mycanvas): doc("emp_base"), my_button([](){}, "Start Tutorial"){
            // Probably want to do this in symAnimate 
            doc << my_button;
            my_button.SetCSS("position", "relative");

            /* First state: No effects, trigger to second when button presed */
            tut.AddState("first_state");
            //tut.AddOverlayEffect("first_state", buttons, "black", 0.5, -1, true);

            /* Second state: from first, to third, overlay and popover*/
            tut.AddState("second_state");

            // Popover remains into the third_state, while overlay does not
            tut.AddPopoverEffect("second_state", buttons, "Click it to start the experiement", "-2.4vh", "-2vw");
            tut.AddPopoverEffect("second_state", buttons, "This is a walk through of the UI", "27vh", "-3vw");
            // tut.AddOverlayEffect("second_state", buttons, "black", 0.8, 10, true);
            // tut.AddCustomVisualEffect("second_state", animation, "z_index","13");
            // Can we change the contents of the start tutorial button sp that it change to end tutorial once we have entered the tutorial
            

            /* third state */
            // tut.AddState("third_state");
            // tut.AddOverlayEffect("third_state", buttons, "yellow", 0.5, -1, true);

            /* End state */
            tut.AddState("end_state", &PrintComplete);


            /* Transitions */
            tut.AddEventListenerTrigger("first_state", "second_state", my_button, "click");
            tut.AddEventListenerTrigger("second_state", "third_state", my_button, "click");
            // tut.AddExistingTrigger("third_state", "end_state", "click");

            
            
            //tut.AddOverlayEffect("end_state", buttons, "black", 0.5,-1, true);
            // tut.AddCSSEffect("first_state", my_button, "z-index", "50000");
            // buttons.Button("toggle").SetCSS("position", "relative");
            // buttons.Button("toggle").SetCSS("z-index", "1");
            // my_button.SetCSS("z-index", "2");
            tut.StartAtState("first_state");
            started=true;

            
        }

        void startTut(UI::Document animation, UI::Document settings, UI::Document explanation, UI::Document learnmore, UI::Document buttons, UI::Canvas mycanvas) {
            if (started) {
                buttons.Button("toggle").SetCSS("position", "relative");
                buttons.Button("toggle").SetCSS("z-index", "11");

            }
            
            // // my_button.SetCSS("z-index", "2");
            // tut.StartAtState("first_state");
        }
};
#endif