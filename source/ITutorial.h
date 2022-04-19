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
template <typename T>
class ITutorial {
    private:
        UI::Document doc;
        UI::Button my_button;
        Tutorial tut;
        UI::Button ok_but;
        UI::Button start_but;

    public:
        static void PrintComplete() { std::cout << "Tutorial Complete!" << std::endl; }

        ITutorial(UI::Document animation, UI::Document settings, UI::Document explanation, UI::Document learnmore, UI::Document buttons, UI:: Document top_bar, UI::Canvas mycanvas): doc("emp_base"), ok_but([](){}, "OK"){
            my_button = buttons.Button("start_but");
            // doc << my_button;
            // top_bar << my_button;
            // my_button.OnMouseOver([this](){auto but  =my_button; but.SetCSS("background-color", "#3d1477"); but.SetCSS("cursor", "pointer"); but.SetCSS("color", "white");});
            // my_button.SetAttr("class", "btn btn-secondary");
            // my_button.OnMouseOut([this](){auto but=my_button; but.SetCSS("background-color", "#5f8eff"); but.SetCSS("color", "white");});
            // my_button.SetCSS("background-color", "#5f8eff");
            // my_button.SetCSS("position", "absolute");
            // my_button.SetCSS("right", "23.5vw");
            // my_button.SetCSS("bottom", "1.5vh");
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
            ok_but.SetCSS("z-index", "13");
            /*start_but_state*/
            tut.AddPopoverEffect("start_but_state", buttons, "This is a walk through of the UI", ok_but, "15vh", "-4vw");
            tut.AddPopoverEffect("start_but_state", buttons, "Click it to start or pause the experiement", ok_but, "-3vh", "-4vw");
            tut.AddOverlayEffect("start_but_state", buttons, buttons, "black", 0.8, 10, true);
            // emp::Ptr<OverlayEffect> overlayPtr = tut.AddOverlayEffect("start_but_state", buttons, "black", 0.8, 10, true);
            // std::string curState = tut.GetCurrentState();
            // std::cout << "Testing......current state: "<< curState<<std::endl;
            // if (curState=="start_but_state") {
            //     overlayPtr -> SetOverlayCSS("position", "relative");
            //     overlayPtr -> SetOverlayCSS("z-index", "10");
            //     overlayPtr -> SetOverlayCSS("background-color", "red");
            // }

            /*reset_but_state*/
            tut.AddPopoverEffect("reset_but_state", buttons, "Click it to reset petri dish", ok_but, "1vh", "0vw");
            tut.AddOverlayEffect("reset_but_state", buttons, settings, "black", 0.8, 10, true);

            /*settings_state*/
            tut.AddPopoverEffect("settings_state", buttons, "This is the settings panel. Drop down to see configurable parameters", ok_but, "-7vh", "-27vw");
            tut.AddOverlayEffect("settings_state", buttons, buttons, "black", 0.8, 10, true);

            /*settings_change_state*/
            tut.AddPopoverEffect("settings_change_state", buttons, "Try to change the parameters and start a new experiment to see the difference", ok_but, "-7vh", "-27vw");
            tut.AddOverlayEffect("settings_change_state", buttons, settings, "black", 0.8, 10, true);

            /*lab_instruct_state*/
            tut.AddPopoverEffect("lab_instruct_state", buttons, "Drop this card down to see lab instructions", ok_but, "-7vh", "30vw");
            tut.AddOverlayEffect("lab_instruct_state", buttons, explanation, "black", 0.8, 10, true);

            /*graph_state*/
            tut.AddPopoverEffect("graph_state", buttons, "Drop this card down to see live graphs of the experiment", ok_but, "1vh", "30vw");
            tut.AddOverlayEffect("graph_state", buttons, explanation, "black", 0.8, 10, true);

            /*repeat_state*/

            /*end_state*/

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

            


            // tut.StartAtState("first_state");
                

        }
};
#endif