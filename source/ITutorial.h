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
        // UI::Button my_button;
        Tutorial tut;
        UI::Button ok_but;
        UI::Button start_but;

    public:
        static void PrintComplete() { std::cout << "Tutorial Complete!" << std::endl; }

        ITutorial(UI::Document animation, UI::Document settings, UI::Document explanation, UI::Document learnmore, UI::Document buttons, UI:: Document top_bar, UI::Canvas mycanvas,UI::Document instructions, UI::Button my_button): doc("emp_base"), ok_but([](){}, "OK"){
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
            tut.AddExistingTrigger("end_state", "start_but_state", "click_trigger");
            ok_but.SetCSS("z-index", "13");
            /*start_but_state*/
            tut.AddPopoverEffect("start_but_state", buttons, "Welcome to Symbulation, an interactive online lab that explores the relationships between hosts and symbionts. Before starting this tutorial, click the symbulation background button to learn about how the simulation runs. Once you have read it, click next.", ok_but, "2vh", "-23vw", "60%");
            tut.AddPopoverEffect("start_but_state", buttons, "This grid represents a petri dish holding the hosts and symbionts in our environment. Each host is a square, and each symbiont is a circle. To start the simulation, just push start and observe as the petri dish starts to change. You can pause the simulation at any time with the pause button. ", ok_but, "2vh", "25vw", "auto");
            tut.AddOverlayEffect("start_but_state", buttons, buttons, "black", 0.8, 10, true);


            /*reset_but_state*/
            tut.AddPopoverEffect("reset_but_state", buttons, "To reset the simulation, push reset. You will need to click reset after you make changes to the settings before starting the simulation.", ok_but, "2vh", "0vw", "auto");
            tut.AddOverlayEffect("reset_but_state", buttons, settings, "black", 0.8, 10, true);
            /*settings_state*/
            tut.AddPopoverEffect("settings_state", buttons, "These are the settings panels. Each setting has a dropdown that explains more about what that setting does. Try expanding a dropdown to learn more about a setting.", ok_but, "2vh", "-5vw", "90%");
            tut.AddOverlayEffect("settings_state", buttons, buttons, "black", 0.8, 10, true);

            /*settings_change_state*/
            tut.AddPopoverEffect("settings_change_state", buttons, "You can change a setting by adjusting the slider, typing in a value, or using the small arrows. Try changing a setting now!", ok_but, "2vh", "-5vw", "90%");
            tut.AddOverlayEffect("settings_change_state", buttons, settings, "black", 0.8, 10, true);
            tut.AddPopoverEffect("settings_change_state", buttons, "After changing your settings, you must push reset to see your changes reflected in the petri dish. Try pushing reset, then starting the simulation again. Did you see the changes?", ok_but, "25vh", "-5vw", "90%");
            

            /*lab_instruct_state*/
            tut.AddPopoverEffect("lab_instruct_state", buttons, "Your lab instructions are held here. Each section can be collapsed to save space on your screen", ok_but, "2vh", "20vw", "auto");
            tut.AddOverlayEffect("lab_instruct_state", buttons, explanation, "black", 0.8, 10, true);

            /*graph_state*/
            tut.AddPopoverEffect("graph_state", buttons, "Below the lab instructions are live graphs. Click the drop down to see them!", ok_but, "30vh", "20vw", "auto");
            tut.AddOverlayEffect("graph_state", buttons, explanation, "black", 0.8, 10, true);

            /*repeat_state*/
            tut.AddPopoverEffect("repeat_state", buttons, "Click reset and start on the lab to watch the graphs update in real time.", ok_but, "2vh", "30vw", "auto");
            tut.AddOverlayEffect("repeat_state", buttons, explanation, "black", 0.8, 10, true);
            
            /*end_state*/
            tut.AddPopoverEffect("end_state", buttons, "You have finished the tutorial! To start it again at any time, click the start tutorial button. If you have any questions, click the FAQ button, or refer to the symbulation background.", ok_but, "2vh", "0vw", "60%");
            tut.AddOverlayEffect("end_state", buttons, explanation, "black", 0.8, 10, true);
            

            //tut.AddExistingTrigger("second_state", "third_state", "click_trigger");
            //tut.AddEventListenerTrigger("third_state", "end_state", ok_but, "click", "click_ok");
            tut.StartAtState("first_state");

        }

        void startTut(UI::Document animation, UI::Document settings, UI::Document explanation, UI::Document learnmore, UI::Document buttons, UI::Canvas mycanvas, UI::Document instructions) {

            ok_but.SetCSS("left", "0.7vw");
            instructions.SetCSS("z-index","0");
            instructions.SetCSS("position", "relative");
            // animation.SetCSS("position", "relative");
            // animation.SetCSS("z-index", "12");
            
            tut.AddSpotlight("start_but_state", animation);
            tut.AddSpotlight("start_but_state", buttons.Button("toggle"));
            tut.AddSpotlight("reset_but_state", buttons.Button("reset"));
            tut.AddSpotlight("settings_state", settings);
            tut.AddSpotlight("settings_change_state", settings);
            


            // tut.StartAtState("first_state");
                

        }
};
#endif