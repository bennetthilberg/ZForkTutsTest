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
            tut.AddState("start_but_state");
            tut.AddState("reset_but_state");
            tut.AddState("settings_state");
            tut.AddState("settings_change_state");
            tut.AddState("lab_instruct_state");
            tut.AddState("graph_state");
            tut.AddState("repeat_state");
            tut.AddState("end_state", &PrintComplete);

            /* All triggers */
            tut.AddEventListenerTrigger("first_state", "start_but_state", my_button, "click", "click_trigger");
            tut.AddEventListenerTrigger("start_but_state", "reset_but_state", ok_but, "click", "click_ok");
            tut.AddExistingTrigger("reset_but_state", "settings_state", "click_ok");
            tut.AddExistingTrigger("settings_state", "settings_change_state", "click_ok");
            tut.AddExistingTrigger("settings_change_state", "lab_instruct_state", "click_ok");
            tut.AddExistingTrigger("lab_instruct_state", "graph_state", "click_ok");
            tut.AddExistingTrigger("graph_state", "repeat_state", "click_ok");
            tut.AddExistingTrigger("repeat_state", "end_state", "click_ok");
            printf("new VVersion!\n");
            /*start_but_state*/
            tut.AddPopoverEffect("start_but_state", buttons, "This is a walk through of the UI", ok_but, "15vh", "-1vw");
            tut.AddPopoverEffect("start_but_state", buttons, "Click it to start the experiement", ok_but, "-0.5vh", "-2vw");
            emp::Ptr<OverlayEffect> overlayPtr = tut.AddOverlayEffect("start_but_state", buttons, "black", 0.8, 10, true);
            if (tut.GetCurrentState()=="start_but_state") {
                overlayPtr -> SetOverlayCSS("position", "relative");
                overlayPtr -> SetOverlayCSS("z-index", "10");
                overlayPtr -> SetOverlayCSS("background-color", "red");
            }
            /**/
            /**/
            /**/
            /**/
            /**/
            /**/
            /**/
            /**/

            ok_but.SetCSS("z-index", "13");
            //tut.AddExistingTrigger("second_state", "third_state", "click_trigger");
            //tut.AddEventListenerTrigger("third_state", "end_state", ok_but, "click", "click_ok");
            tut.StartAtState("first_state");

        }

        void startTut(UI::Document animation, UI::Document settings, UI::Document explanation, UI::Document learnmore, UI::Document buttons, UI::Canvas mycanvas) {
            start_but = buttons.Button("toggle");

            start_but.SetCSS("position", "relative");
            start_but.SetCSS("z-index", "11");
            ok_but.SetCSS("left", "0.7vw");

            animation.SetCSS("position", "relative");
            animation.SetCSS("z-index", "12");

            
    
            
            // /* Popovers */
            // tut.AddPopoverEffect("second_state", buttons, "This is a walk through of the UI", ok_but, "15vh", "-1vw");
            // tut.AddPopoverEffect("second_state", buttons, "Click it to start the experiement", ok_but, "-0.5vh", "-2vw");




            // tut.StartAtState("first_state");
                

        }
};
#endif