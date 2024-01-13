#ifndef ITUTORIAL_H
#define ITUTORIAL_H
#include "../../Empirical/include/emp/web/KeypressManager.hpp"
#include "../../Empirical/include/emp/web/Tutorial.h"
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
 
        ITutorial(UI::Document & animation, UI::Document & settings, UI::Document & explanation, UI::Document & learnmore, UI::Document & buttons, UI::Document & top_bar, UI::Canvas & mycanvas,UI::Document & instructions, UI::Document & graphs, UI::Button & my_button): doc("emp_base"), ok_but([](){}, "OK"){
            
            ok_but.SetCSS("position", "relative");
            ok_but.SetCSS("z-index", "13");
            my_button.SetCSS("z-index", "13");
            
            printf("testing");
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
            // tut.AddState("end_state", &PrintComplete);
 
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
            tut.AddExistingTrigger("repeat_state", "first_state", "click_ok");

            /*end tutorial triggers*/
            // Next line is supposed to allow you to restart the tutorial, but instead we are getting it automaticallly entering
            // this state rather than waiting for the trigger :(
            //tut.AddExistingTrigger("end_state", "first_state", "click_trigger");
            // tut.AddExistingTrigger("intro_state", "end_state", "click_trigger");
            // tut.AddExistingTrigger("start_but_state", "end_state", "click_trigger");
            // tut.AddExistingTrigger("reset_but_state", "end_state", "click_trigger");
            // tut.AddExistingTrigger("settings_state", "end_state", "click_trigger");
            // tut.AddExistingTrigger("settings_change_state", "end_state", "click_trigger");
            // tut.AddExistingTrigger("reset_change_state", "end_state", "click_trigger");
            // tut.AddExistingTrigger("lab_instruct_state", "end_state", "click_trigger");
            // tut.AddExistingTrigger("graph_state", "end_state", "click_trigger");
            // tut.AddExistingTrigger("repeat_state", "end_state", "click_trigger");
            
            tut.AddExistingTrigger("intro_state", "first_state", "click_trigger");
            tut.AddExistingTrigger("start_but_state", "first_state", "click_trigger");
            tut.AddExistingTrigger("reset_but_state", "first_state", "click_trigger");
            tut.AddExistingTrigger("settings_state", "first_state", "click_trigger");
            tut.AddExistingTrigger("settings_change_state", "first_state", "click_trigger");
            tut.AddExistingTrigger("reset_change_state", "first_state", "click_trigger");
            tut.AddExistingTrigger("lab_instruct_state", "first_state", "click_trigger");
            tut.AddExistingTrigger("graph_state", "first_state", "click_trigger");
            tut.AddExistingTrigger("repeat_state", "first_state", "click_trigger");


            /*start_but_state*/
            tut.AddPopoverEffect("intro_state", buttons, "Welcome to Symbulation, an interactive online lab for Symbiosis. Before starting this tutorial, click the Symbulation Overview button to learn about how the simulation runs. Once you have read it, click ok.", ok_but, "1vh", "-4vw", "auto");
            tut.AddOverlayEffect("intro_state", buttons, "black", 0.8, 10, true);
            
            tut.AddPopoverEffect("start_but_state", buttons, "This grid represents a petri dish holding the hosts and symbionts in our environment. Each host is a square, and each symbiont is a circle. Press Start to start the experiment, and press Pause when you want to pause it", ok_but, "-6vh", "-4vw", "auto");
            tut.AddOverlayEffect("start_but_state", buttons, "black", 0.8, 10, true);
            // emp::Ptr<OverlayEffect> overlayPtr = tut.AddOverlayEffect("start_but_state", buttons, "black", 0.8, 10, true);
            // std::string curState = tut.GetCurrentState();
            // std::cout << "Testing......current state: "<< curState<<std::endl;
            // if (curState=="start_but_state") {
            //     overlayPtr -> SetOverlayCSS("position", "relative");
            //     overlayPtr -> SetOverlayCSS("z-index", "10");
            //     overlayPtr -> SetOverlayCSS("background-color", "red");
            // }
 
            /*reset_but_state*/
            tut.AddPopoverEffect("reset_but_state", buttons, "Press Reset to start a new experiment", ok_but, "0.4vh", "-5vw", "auto");
            tut.AddOverlayEffect("reset_but_state", buttons, "black", 0.8, 10, true);
            /*settings_state*/
            tut.AddPopoverEffect("settings_state", buttons, "These are the settings panels. Click on each term to see its explantion. Try it.", ok_but, "1vh", "-5vw", "auto");
            tut.AddOverlayEffect("settings_state", buttons,  "black", 0.8, 10, true);
 
            /*settings_change_state*/

            tut.AddPopoverEffect("settings_change_state", buttons, "You can change a setting by adjusting the slider, typing in a value, or using the small arrows. Try changing a setting now!", ok_but, "1vh", "-5vw", "auto");
            tut.AddOverlayEffect("settings_change_state", buttons, "black", 0.8, 10, true);
 
            /*reset_change_state*/
            tut.AddPopoverEffect("reset_change_state", buttons, "To apply the changes in the settings, push Reset and then Start. Did you notice any difference?", ok_but, "-2vh", "-4vw", "auto");
            tut.AddOverlayEffect("reset_change_state", buttons, "black", 0.8, 10, true);
            
            /*lab_instruct_state*/
            tut.AddPopoverEffect("lab_instruct_state", buttons, "Lab instructions are held here. Each section can be collapsed", ok_but, "1vh", "12vw", "70%");
            tut.AddOverlayEffect("lab_instruct_state", buttons, "black", 0.8, 10, true);
 
            /*graph_state*/
            tut.AddPopoverEffect("graph_state", buttons, "Live graphs are below the instructions. Drop down to see them!", ok_but, "35vh", "25vw", "40%");
            tut.AddPopoverEffect("graph_state", buttons, "Try starting a new experiment and watching the graphs update in real time! ", ok_but, "46vh", "25vw", "40%");
            tut.AddOverlayEffect("graph_state", buttons, "black", 0.8, 10, true);
 
            /*repeat_state*/
            tut.AddPopoverEffect("repeat_state", buttons, "Tutorial finished! To see it agian, click the Start Tutorial button. Click the FAQ button, or refer to the symbulation background, if you have more questions ", ok_but, "1vh", "-4vw", "auto");
            tut.AddOverlayEffect("repeat_state", buttons, "black", 0.8, 10, true);
 
            /*end_state*/

            tut.StartAtState("intro_state", my_button);
 
        }
 
        void startTut(UI::Document & animation, UI::Document & settings, UI::Document & explanation, UI::Document & learnmore, UI::Document & buttons, UI::Canvas & mycanvas, UI::Document & instructions,UI::Document & graphs, UI::Document & top_bar) {
 
            ok_but.SetCSS("left", "0.7vw");


            tut.AddSpotlight("intro_state", top_bar);
            tut.AddSpotlight("start_but_state", animation);
            tut.AddSpotlight("start_but_state", buttons.Button("toggle"));
            tut.AddSpotlight("reset_but_state", buttons.Button("reset"));
            tut.AddSpotlight("reset_but_state", animation);
            tut.AddSpotlight("settings_state", settings);
            tut.AddSpotlight("settings_change_state", settings);
            tut.AddSpotlight("reset_change_state", settings);
            tut.AddSpotlight("reset_change_state", buttons.Button("reset"));
            tut.AddSpotlight("reset_change_state", animation);
            tut.AddSpotlight("reset_change_state", buttons.Button("toggle"));
            tut.AddSpotlight("lab_instruct_state", instructions);
            tut.AddSpotlight("graph_state", graphs);


            tut.AddSpotlight("first_state", instructions);
            tut.AddSpotlight("first_state", graphs);
            instructions.SetCSS("z-index","-1");
            instructions.SetCSS("position", "relative");
            graphs.SetCSS("z-index","-1");
            graphs.SetCSS("position", "relative");
            top_bar.SetCSS("z-index", "12");
           
 
                
 
        }
};
#endif

