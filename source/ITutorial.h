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
        Tutorial tut;
        UI::Button ok_but;
        UI::Button start_but;
 
    public:
        static void PrintComplete() { std::cout << "Tutorial Complete!" << std::endl; }
 
        ITutorial(UI::Document & animation, UI::Document & settings, UI::Document & explanation, UI::Document & learnmore, UI::Document & buttons, UI::Document & top_bar, UI::Canvas & mycanvas,UI::Document & instructions, UI::Button & my_button): doc("emp_base"), ok_but([](){}, "OK"){
            
            ok_but.SetCSS("position", "relative");
            ok_but.SetCSS("z-index", "13");
            my_button.SetCSS("z-index", "13");
 
            /* Add all states */
            tut.AddState("first_state");
            tut.AddState("intro_state");
            tut.AddState("start_but_state");
            tut.AddState("reset_but_state");
            tut.AddState("settings_state");
            tut.AddState("settings_change_state");
            tut.AddState("reset_change_state");
            tut.AddState("lab_instruct_state");
            tut.AddState("graph_state");
            tut.AddState("repeat_state");
            tut.AddState("end_state", &PrintComplete);
 
            /* All state-to-state triggers */
            tut.AddEventListenerTrigger("first_state", "intro_state", my_button, "click", "click_trigger");
            tut.AddEventListenerTrigger("intro_state", "start_but_state", ok_but, "click", "click_ok");
            tut.AddExistingTrigger("start_but_state", "reset_but_state", "click_ok");
            tut.AddExistingTrigger("reset_but_state", "settings_state", "click_ok");
            tut.AddExistingTrigger("settings_state", "settings_change_state", "click_ok");
            tut.AddExistingTrigger("settings_change_state", "reset_change_state", "click_ok");
            tut.AddExistingTrigger("reset_change_state", "lab_instruct_state", "click_ok");
            tut.AddExistingTrigger("lab_instruct_state", "graph_state", "click_ok");
            tut.AddExistingTrigger("graph_state", "repeat_state", "click_ok");
            tut.AddExistingTrigger("repeat_state", "end_state", "click_ok");

            /*end tutorial triggers*/
            // Next line is supposed to allow you to restart the tutorial, but instead we are getting it automaticallly entering
            // this state rather than waiting for the trigger :(
            //tut.AddExistingTrigger("end_state", "first_state", "click_trigger");
            tut.AddExistingTrigger("intro_state", "end_state", "click_trigger");
            tut.AddExistingTrigger("start_but_state", "end_state", "click_trigger");
            tut.AddExistingTrigger("reset_but_state", "end_state", "click_trigger");
            tut.AddExistingTrigger("settings_state", "end_state", "click_trigger");
            tut.AddExistingTrigger("settings_change_state", "end_state", "click_trigger");
            tut.AddExistingTrigger("reset_change_state", "end_state", "click_trigger");
            tut.AddExistingTrigger("lab_instruct_state", "end_state", "click_trigger");
            tut.AddExistingTrigger("graph_state", "end_state", "click_trigger");
            tut.AddExistingTrigger("repeat_state", "end_state", "click_trigger");

            /*start_but_state*/
            tut.AddPopoverEffect("intro_state", buttons, "Welcome to Symbulation, an interactive online lab that explores the relationships between hosts and symbionts. Before starting this tutorial, click the symbulation background button to learn about how the simulation runs. Once you have read it, click ok.", ok_but, "1vh", "-4vw", "auto");
            tut.AddOverlayEffect("intro_state", buttons, buttons, "black", 0.8, 10, true);
            
            tut.AddPopoverEffect("start_but_state", buttons, "This grid represents a petri dish holding the hosts and symbionts in our environment. Each host is a square, and each symbiont is a circle. To start the simulation, just push start and observe as the petri dish starts to change. You can pause the simulation at any time with the pause button.", ok_but, "-10vh", "-4vw", "auto");
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
            tut.AddPopoverEffect("reset_but_state", buttons, "To reset the simulation, push reset. You will need to click reset after you make changes to the settings before starting the simulation.", ok_but, "1vh", "-5vw", "auto");
            tut.AddOverlayEffect("reset_but_state", buttons, settings, "black", 0.8, 10, true);
            /*settings_state*/
            tut.AddPopoverEffect("settings_state", buttons, "These are the settings panels. Each setting has a dropdown that explains more about what that setting does. Try expanding a dropdown to learn more about a setting. ", ok_but, "1vh", "-5vw", "auto");
            tut.AddOverlayEffect("settings_state", buttons, buttons, "black", 0.8, 10, true);
 
            /*settings_change_state*/
            tut.AddPopoverEffect("settings_change_state", buttons, "You can change a setting by adjusting the slider, typing in a value, or using the small arrows. Try changing a setting now!", ok_but, "1vh", "-5vw", "auto");
            tut.AddOverlayEffect("settings_change_state", buttons, settings, "black", 0.8, 10, true);
 
            /*reset_change_state*/
            tut.AddPopoverEffect("reset_change_state", buttons, "After changing your settings, you must push reset to see your changes reflected in the petri dish. Try pushing reset, then starting the simulation again. Did you see the changes?", ok_but, "-5vh", "-4vw", "auto");
            tut.AddOverlayEffect("reset_change_state", buttons, settings, "black", 0.8, 10, true);
            
            /*lab_instruct_state*/
            tut.AddPopoverEffect("lab_instruct_state", buttons, "Your lab instructions are held here. Each section can be collapsed to save space on your screen", ok_but, "1vh", "10vw", "70%");
            tut.AddOverlayEffect("lab_instruct_state", buttons, explanation, "black", 0.8, 10, true);
 
            /*graph_state*/
            tut.AddPopoverEffect("graph_state", buttons, "Below the lab instructions are live graphs. Click the drop down to see them!", ok_but, "20vh", "25vw", "40%");
            tut.AddPopoverEffect("graph_state", buttons, "Click reset and start on the lab to watch the graphs update in real time. ", ok_but, "30vh", "25vw", "40%");
            tut.AddOverlayEffect("graph_state", buttons, explanation, "black", 0.8, 10, true);
 
            /*repeat_state*/
            tut.AddPopoverEffect("repeat_state", buttons, "You have finished the tutorial! To start it again at any time, click the start tutorial button. If you have any questions, click the FAQ button, or refer to the symbulation background. ", ok_but, "1vh", "-4vw", "auto");
            tut.AddOverlayEffect("repeat_state", buttons, explanation, "black", 0.8, 10, true);
 
            /*end_state*/

            tut.StartAtState("first_state");
 
        }
 
        void startTut(UI::Document & animation, UI::Document & settings, UI::Document & explanation, UI::Document & learnmore, UI::Document & buttons, UI::Canvas & mycanvas, UI::Document & instructions, UI::Document & top_bar) {
 
            ok_but.SetCSS("left", "0.7vw");
            instructions.SetCSS("z-index","0");
            instructions.SetCSS("position", "static");
            // animation.SetCSS("position", "relative");
            // animation.SetCSS("z-index", "12");
            tut.AddSpotlight("first_state", instructions);
            tut.AddSpotlight("start_but_state", animation);
            tut.AddSpotlight("start_but_state", buttons.Button("toggle"));
            tut.AddSpotlight("reset_but_state", buttons.Button("reset"));
            //tut.AddSpotlight("settings_state", settings.Div("emp__449_MAIN_outer_card_header"));
            //tut.AddSpotlight("settings_state", settings.Div("emp__449_HOST_outer_card_header"));
            //tut.AddSpotlight("settings_state", settings.Div("emp__449_SYM_outer_card_header"));
            //tut.AddSpotlight("settings_state", settings.Div("emp__449_ADV_outer_card_header"));
            tut.AddSpotlight("settings_state", settings);
            tut.AddSpotlight("settings_change_state", settings);
            tut.AddSpotlight("intro_state", top_bar);
            tut.AddSpotlight("graph_state", buttons);
            tut.AddSpotlight("reset_change_state", buttons);
           
 
 
            // tut.StartAtState("first_state");
               
 
        }
};
#endif

