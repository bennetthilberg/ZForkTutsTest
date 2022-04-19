// This file contains all operations related to the web interface
#ifndef SYM_ANIMATE_H
#define SYM_ANIMATE_H

#include <iostream>
#include "default_mode/SymWorld.h"
#include "ConfigSetup.h"
//#include "SymJS.h"
#include "default_mode/Symbiont.h"
#include "default_mode/Host.h"
#include "../Empirical/include/emp/web/Document.hpp"
#include "../Empirical/include/emp/web/Canvas.hpp"
#include "../Empirical/include/emp/web/web.hpp"
#include "../Empirical/include/emp/config/ArgManager.hpp"
#include "../Empirical/include/emp/prefab/ConfigPanel.hpp"
#include "../Empirical/include/emp/web/UrlParams.hpp"
#include "default_mode/WorldSetup.cc"
#include "SymConfigPanel.h"
#include "ITutorial.h"

#include "../Empirical/include/emp/web/d3/d3_init.hpp"
#include "../Empirical/include/emp/web/Document.hpp"
#include "../Empirical/include/emp/web/d3/visualizations.hpp"
#include "../Empirical/include/emp/web/d3/selection.hpp"

namespace UI = emp::web;
SymConfigBase config; // load the default configuration


class SymAnimate : public UI::Animate {
private:

  UI::Document animation;
  UI::Document top_bar;
  UI::Button start_tutorial;
  UI::Document settings;
  UI::Document explanation;
  UI::Document graphs; 
  UI::Document learnmore;
  UI::Document buttons;
  UI::Document instructions;
  UI::Canvas mycanvas;
  UI::Canvas host_graph_canvas;
  UI::Canvas sym_graph_canvas;
  UI::Canvas sym_histogram_canvas; 
  UI::Canvas host_histogram_canvas;  
  ITutorial itut;
  const int RECT_WIDTH = 10;
  const int UPDATE_HIST = 50;
  const int GRAPH_PADDING_X = 30;
  const double GRAPH_PADDING_Y = 0.15; 

  emp::Random random{config.SEED()};
  SymWorld world{random};


  emp::vector<emp::Ptr<Organism>> p;


  int num_mutualistic = 0;
  int num_parasitic = 0;

public:

  /**
   * 
   * The contructor for SymAnimate
   * 
   */
  SymAnimate() : animation("emp_animate"), graphs("graphs"), settings("emp_settings"), explanation("emp_explanation"), learnmore("emp_learnmore"), buttons("emp_buttons"), instructions("instructions"), top_bar("top_bar"), start_tutorial([](){}, "Start Tutorial"), itut(animation, settings, explanation, learnmore, buttons, top_bar, mycanvas, instructions, start_tutorial){

    config.GRID_X(40);
    config.GRID_Y(40);
    config.UPDATES(1000);
    SymConfigPanel config_panel(config);
    //Exclude all the settings that control
    //things that don't show up in the GUI correctly
    config_panel.ExcludeSetting("SYM_LIMIT");
    config_panel.ExcludeSetting("DATA_INT");
    config_panel.ExcludeSetting("POP_SIZE");
    config_panel.ExcludeSetting("LYSIS");
    config_panel.ExcludeSetting("BURST_SIZE");
    config_panel.ExcludeSetting("BURST_TIME");
    config_panel.ExcludeSetting("SYM_LYSIS_RES");
    config_panel.ExcludeSetting("START_MOI");
    config_panel.ExcludeSetting("FILE_PATH");
    config_panel.ExcludeSetting("FILE_NAME");
    config_panel.ExcludeSetting("COMPETITION_MODE");
    config_panel.ExcludeSetting("HORIZ_TRANS");
    config_panel.ExcludeSetting("UPDATES");
    config_panel.ExcludeSetting("GRID_X");
    config_panel.ExcludeSetting("GRID_Y");
    config_panel.ExcludeGroup("LYSIS");
    config_panel.ExcludeGroup("EFF");
    config_panel.ExcludeGroup("PGG");


    config_panel.SetRange("SYNERGY","-10","10");
    config_panel.SetRange("MUTATION_SIZE","-0.2","0.2");
    config_panel.SetRange("HOST_INT","-1","1");
    config_panel.SetRange("SYM_INT","-2","1");//need to change 

    top_bar.SetAttr("class", "topBar");
    top_bar.SetCSS("position", "relative");
    top_bar.SetCSS("height", "10vh");
    animation.SetCSS("position", "static");
    animation.SetCSS("flex-grow", "1");
    animation.SetCSS("max-width", "500px");
    instructions.SetCSS("flex-grow", "1");
    instructions.SetCSS("max-width", "500px");
    graphs.SetCSS("flex-grow", "1");
    graphs.SetCSS("max-width", "500px");
    settings.SetCSS("flex-grow", "1");
    settings.SetCSS("max-width", "600px");
    explanation.SetCSS("flex-grow", "1");
    explanation.SetCSS("max-width", "600px");
    learnmore.SetCSS("flex-grow", "1");
    learnmore.SetCSS("max-width", "600px");
    buttons.SetCSS("flex-grow", "1");
    buttons.SetCSS("max-width", "600px");

    start_tutorial.OnMouseOver([this](){auto but  =start_tutorial;});
    start_tutorial.SetAttr("class", "test1");
    start_tutorial.OnMouseOut([this](){auto but=start_tutorial;});
    // start_tutorial.SetCSS("background-color", "#5f8eff");
    // start_tutorial.SetCSS("position", "absolute");
    // start_tutorial.SetCSS("right", "23.5vw");
    // start_tutorial.SetCSS("bottom", "1.5vh");

    top_bar << "<div class=\"rightB\">";
    top_bar << "<button class=\"test1\" onclick = 'f=window.open(\"FAQ.html\",\"fenetre\",\"the style (without style tag, example - width=400, height=600, no px\")'style=\"cursor: pointer;\">FAQ</button>";
    top_bar << start_tutorial;
    top_bar << "<button class=\"test1\" onclick = 'f=window.open(\"biology_background.html\",\"fenetre\",\"the style (without style tag, example - width=400, height=600, no px\")'style=\"cursor: pointer;\">Biology Background</button>";
    top_bar << "<button class=\"test1\" onclick = 'f=window.open(\"symb_overview.html\",\"fenetre\",\"the style (without style tag, example - width=400, height=600, no px\")'style=\"cursor: pointer;\">Symbulation Overview</button>";
    top_bar << "<a href=\"https://anyaevostinar.github.io/SymbulationEmp/web/symbulation.html\" ><button class=\"test1\">Home GUI</button></a>";
    top_bar << "</div>";

    initializeWorld();
    /*
    emp::prefab::Card config_panel_ex("INIT_CLOSED");
    settings << config_panel_ex;
    config_panel_ex.AddHeaderContent("<h3>Settings</h3>");
    */

    // apply configuration query params and config files to config
    auto specs = emp::ArgManager::make_builtin_specs(&config);
    emp::ArgManager am(emp::web::GetUrlParams(), specs);
    // cfg.Read("config.cfg");
    am.UseCallbacks();
    if (am.HasUnused()) std::exit(EXIT_FAILURE);

    // setup configuration panel
    //config_panel.Setup();
    // config_panel_ex << config_panel;
    settings << config_panel;


    // Add explanation for organism color:
    explanation << "<img style=\"max-width:350px;\" src = \"gradient1.png\"/> <br>";


    // ----------------------- Add a button that allows for pause and start toggle -----------------------
    buttons << "<br>" << "<br><img style=\"max-width:175px;\" src=\"diagram.png\">";
    buttons.AddButton([this](){
      // animate up to the number of updates
      ToggleActive();
      auto but = buttons.Button("toggle");
      if (GetActive()) but.SetLabel("Pause");
      else but.SetLabel("Start");
    }, "Start", "toggle");
    
    setButtonStyle("toggle");
    buttons.Button("toggle").OnMouseOver([this](){ auto but = buttons.Button("toggle"); but.SetCSS("background-color", "#3d1477"); but.SetCSS("cursor", "pointer"); but.SetCSS("color", "white");});
    buttons.Button("toggle").OnMouseOut([this](){ auto but = buttons.Button("toggle"); but.SetCSS("background-color", "#5f8eff"); but.SetCSS("color", "white");});


    // ----------------------- Add a reset button to reset the animation/world -----------------------
    /* Note: Must first run world.Reset(), because Inject checks for valid position.
      If a position is occupied, new org is deleted and your world isn't reset.
      Also, canvas must be redrawn to let users see that it is reset */
    buttons.AddButton([this](){
      world.Reset();
      initializeWorld();
      p = world.GetPop();

      if (GetActive()) { // If animation is running, stop animation and adjust button label
        ToggleActive();
      }
      auto but = buttons.Button("toggle");
      but.SetLabel("Start");

      // redraw petri dish
      mycanvas.SetWidth(RECT_WIDTH*config.GRID_X());
      mycanvas.SetHeight(RECT_WIDTH*config.GRID_Y());
      drawPetriDish(mycanvas);
      //graph_canvas.setWidth(750);
      //graph_canvas.setHeight(200);

      host_graph_canvas.Clear();
      initializeGraph(host_graph_canvas, "Host Interaction Values");

      sym_graph_canvas.Clear();
      initializeGraph(sym_graph_canvas, "Symbiont Interaction Values");

      sym_histogram_canvas.Clear();
      initializeStackedHist(sym_histogram_canvas, "Symbiont Interaction Values Distribution");

      host_histogram_canvas.Clear();
      initializeStackedHist(host_histogram_canvas, "Host Interaction Values Distribution");

      ToggleActive();//turn on quick to update the grid if the size changed
      ToggleActive();//turn off again
    }, "Reset", "reset");
    setButtonStyle("reset");
    buttons.Button("toggle").OnMouseOver([this](){ auto but = buttons.Button("toggle"); but.SetCSS("background-color", "#3d1477"); but.SetCSS("cursor", "pointer"); but.SetCSS("color", "white");});
    buttons.Button("toggle").OnMouseOut([this](){ auto but = buttons.Button("toggle"); but.SetCSS("background-color", "#5f8eff"); but.SetCSS("color", "white");});

    buttons.Button("reset").SetAttr("class","btn btn-secondary");
    buttons.Button("toggle").SetAttr("class","btn btn-secondary");
    buttons.Button("toggle").SetAttr("data-toggle","popover");
    buttons.Button("toggle").SetAttr("data-content","Click to start the experiment");
    buttons.Button("toggle").SetAttr("data-container","body");
    //  data-container="body" data-toggle="popover" data-placement="top" data-content="Vivamus sagittis lacus vel augue laoreet rutrum faucibus.">)
    
    // ----------------------- Keep track of number of updates -----------------------
    buttons << "<br>";
    buttons << UI::Text("update") << "Update = " << UI::Live( [this](){ return world.GetUpdate(); } ) << "  ";
    buttons << "<br>";

    // Add a canvas for petri dish and draw the initial petri dish
    mycanvas = animation.AddCanvas(RECT_WIDTH*config.GRID_X(), RECT_WIDTH*config.GRID_Y(), "can");
    targets.push_back(mycanvas);
    drawPetriDish(mycanvas);
    animation << "<br>";

    itut.startTut(animation, settings, explanation, learnmore, buttons, mycanvas, instructions);

    emp::prefab::Card graphs_card(false ? "INIT_OPEN" : "INIT_CLOSED", true, "graphs_card");
    graphs_card.AddHeaderContent("Data Collection");
    graphs_card.SetCSS("background", "#ede9e8");
    graphs_card.SetCSS("font-family", "Garamond");
    graphs_card.SetCSS("letter-spacing", "2px");
    graphs_card.SetCSS("color", "#3d1477");
    graphs_card.SetWidth(100,"%");

    host_graph_canvas = UI::Canvas(RECT_WIDTH*35, RECT_WIDTH*18, "host_graph").SetCSS("background", "white");
    targets.push_back(host_graph_canvas);
    initializeGraph(host_graph_canvas, "Host Interaction Values");

    host_histogram_canvas = UI::Canvas(RECT_WIDTH*35, RECT_WIDTH*18, "host_histogram").SetCSS("background", "white");
    targets.push_back(host_histogram_canvas);
    initializeStackedHist(host_histogram_canvas, "Host Interaction Values Distribution");

    sym_histogram_canvas = UI::Canvas(RECT_WIDTH*35, RECT_WIDTH*18, "sym_histogram").SetCSS("background", "white");
    targets.push_back(sym_histogram_canvas);
    initializeStackedHist(sym_histogram_canvas, "Symbiont Interaction Values Distribution");

    sym_graph_canvas = UI::Canvas(RECT_WIDTH*35, RECT_WIDTH*18, "sym_graph").SetCSS("background", "white");
    targets.push_back(sym_graph_canvas);
    initializeGraph(sym_graph_canvas, "Symbiont Interaction Values");
    
    graphs_card << sym_graph_canvas;
    graphs_card << "<br>";
    graphs_card << host_graph_canvas;
    graphs_card << "<br>";
    graphs_card << sym_histogram_canvas;
    graphs_card << "<br>";
    graphs_card << host_histogram_canvas;
    graphs << graphs_card;

    emp::prefab::Card card_instructions(true ? "INIT_OPEN" : "INIT_CLOSED", true, "instructions_card");
    initializeInstructionsCard(card_instructions);
    instructions << card_instructions;
    itut.startTut(animation, settings, explanation, learnmore, buttons, mycanvas, instructions);
    
  }

  void initializeInstructionsCard(emp::prefab::Card & card){
    card.AddHeaderContent("Lab Instructions");
    card.SetCSS("background", "#ede9e8");
    card.SetCSS("font-family", "Garamond");
    card.SetCSS("letter-spacing", "2px");
    card.SetCSS("color", "#3d1477");
    card.SetWidth(100,"%");

    emp::prefab::Card prelab(true ? "INIT_OPEN" : "INIT_CLOSED", true, "prelab_card");
    prelab.AddHeaderContent("Part 1: Prelab");
    prelab.SetCSS("background", "#ede9e8");
    prelab.SetCSS("font-family", "Garamond");
    prelab.SetCSS("letter-spacing", "2px");
    prelab.SetCSS("color", "#3d1477");
    prelab.SetWidth(100,"%");
    prelab << "example text 2";

    card << prelab;

    emp::prefab::Card lab(false ? "INIT_OPEN" : "INIT_CLOSED", true, "lab_card");
    lab.AddHeaderContent("Part 2: Lab");
    lab.SetCSS("background", "#ede9e8");
    lab.SetCSS("font-family", "Garamond");
    lab.SetCSS("letter-spacing", "2px");
    lab.SetCSS("color", "#3d1477");
    lab.SetWidth(100,"%");
    lab << "example text 3";

    card << lab;


    emp::prefab::Card postlab(false ? "INIT_OPEN" : "INIT_CLOSED", true, "postlab_card");
    postlab.AddHeaderContent("Part 3: Postlab");
    postlab.SetCSS("background", "#ede9e8");
    postlab.SetCSS("font-family", "Garamond");
    postlab.SetCSS("letter-spacing", "2px");
    postlab.SetCSS("color", "#3d1477");
    postlab.SetWidth(100,"%");
    postlab << "example text 4";

    card << postlab;
  }
  
  void initializeGraph(UI::Canvas & can, std::string title){
    //fill in the line, give title, label axes
    int width = can.GetWidth();
    int height = can.GetHeight();

    can.Font("Garamond");
    //can.SetCSS("font-family", "Garamond");

    //horizontal axis - leave a 20px padding for y-axis label
    can.Line(GRAPH_PADDING_X, height/2, width - GRAPH_PADDING_X, height/2);
    //vertical axis - leave 15% of canvas at top and bottom for title and x-axis label
    can.Line(GRAPH_PADDING_X, height*(1-GRAPH_PADDING_Y), GRAPH_PADDING_X, height*GRAPH_PADDING_Y);

    //title
    can.CenterText(width/2, height*(GRAPH_PADDING_Y/2), title);
    //x-axis
    can.CenterText(width/2, height*(1-(GRAPH_PADDING_Y/2)), "Evolutionary Time");
    //can.fillText()
    can.CenterText(20, height*(GRAPH_PADDING_Y), "1");
    can.CenterText(20, height*(1-(GRAPH_PADDING_Y)), "-1");
  }

  void initializeStackedHist(UI::Canvas & can, std::string title){
     //fill in the line, give title, label axes
    int width = can.GetWidth();
    int height = can.GetHeight();

    can.Font("Garamond");
    //can.SetCSS("font-family", "Garamond");

    // horizontal axis - leave padding for y-axis label
    can.Line(GRAPH_PADDING_X, height*(1-GRAPH_PADDING_Y), width - GRAPH_PADDING_X, height*(1-GRAPH_PADDING_Y));
    //vertical axis - leave 15% of canvas at top and bottom for title and x-axis label
    can.Line(GRAPH_PADDING_X, height*(1-GRAPH_PADDING_Y), GRAPH_PADDING_X, height*GRAPH_PADDING_Y);

    //title
    can.CenterText(width/2, height*(GRAPH_PADDING_Y/2), title);
    //x-axis
    can.CenterText(width/2, height*(1-(GRAPH_PADDING_Y/2)), "Evolutionary Time");
    can.CenterText(15, height*(GRAPH_PADDING_Y), "100%");
    can.CenterText(15, height*(1-(GRAPH_PADDING_Y)), "0%");    
  }
  /**
   * Input: None
   * 
   * Output: None
   * 
   * Purpose: To initialize the world based upon the config setting given 
   */
  void initializeWorld(){
     // Reset the seed and the random machine of world to ensure consistent result (??)
    random.ResetSeed(config.SEED());
    world.SetRandom(random);

    worldSetup(&world, &config);

    p = world.GetPop();

  }


  /**
   * Input: The string representing the button identification. 
   * 
   * Output: None
   * 
   * Purpose: To add style to the buttons displayed. 
   */
  void setButtonStyle(std::string but_id){
    auto but = buttons.Button(but_id);
    but.SetCSS("background-color", "#5f8eff");
    but.SetCSS("border-radius", "4px");
    but.SetCSS("margin-left", "5px");
    but.SetCSS("color", "white");
    but.SetCSS("font-family", "Garamond");
    but.SetCSS("letter-spacing", "3px");
    but.SetCSS("font-size", "20px");
  }

  void drawSymStackedHist(UI::Canvas & can){
    int height = can.GetHeight();
    int width = can.GetWidth();
    double graph_height = height * (1 - (2*GRAPH_PADDING_Y));
    int binNum = world.GetUpdate()/UPDATE_HIST;

    int pop_size = 0;
    int i = 0;
    int mut_total = 0; 
    int par_total = 0; 
    int highly_mut_total = 0; 
    int highly_par_total = 0;     
    int neu_total = 0;     
    for (int x = 0; x < config.GRID_X(); x++){
            for (int y = 0; y < config.GRID_Y(); y++){
                //syms
                emp::vector<emp::Ptr<Organism>> syms = p[i]->GetSymbionts();
                for (int j = 0; j  < syms.size(); j++){
                  double val =  syms[j]->GetIntVal();
                  if(val >= 0.6){
                    highly_mut_total += 1;
                  } else if (val < 0.6 && val >= 0.2){
                    mut_total+=1;
                  } else if (val < 0.2 && val >= -0.2){
                    neu_total+=1;
                  } else if (val < -0.2 && val >= -0.7){
                    par_total+=1;
                  } else{
                    highly_par_total+=1; 
                  }
                  pop_size++;
                }
                i++;
            }
    }

    std::string highly_mut_color = matchColor(1.0);
    std::string mut_color = matchColor(0.59);    
    std::string neu_color = matchColor(0.19);
    std::string par_color = matchColor(-0.21);
    std::string highly_par_color = matchColor(-0.61);    
    int binWidth = (width-(2*GRAPH_PADDING_X))/(1000/UPDATE_HIST);
    double highMutEndPoint = height*GRAPH_PADDING_Y + graph_height*highly_mut_total/pop_size;
    double mutEndPoint = highMutEndPoint + graph_height*mut_total/pop_size;
    double neuEndPoint = mutEndPoint + graph_height*neu_total/pop_size;
    double parEndPoint = neuEndPoint + graph_height*par_total/pop_size;
    //int highParBeginPoint = (height*0.7) + parBeginPoint;
    can.Rect(binNum*binWidth + GRAPH_PADDING_X, height*GRAPH_PADDING_Y, binWidth, graph_height*highly_mut_total/pop_size, highly_mut_color); 
    can.Rect(binNum*binWidth + GRAPH_PADDING_X, highMutEndPoint, binWidth, graph_height*mut_total/pop_size, mut_color);   
    can.Rect(binNum*binWidth + GRAPH_PADDING_X, mutEndPoint, binWidth, graph_height*neu_total/pop_size, neu_color);   
    can.Rect(binNum*binWidth + GRAPH_PADDING_X, neuEndPoint, binWidth, graph_height*par_total/pop_size, par_color);   
    can.Rect(binNum*binWidth + GRAPH_PADDING_X, parEndPoint, binWidth, graph_height*highly_par_total/pop_size, highly_par_color);
  }

  void drawHostStackedHist(UI::Canvas & can){
    int height = can.GetHeight();
    int width = can.GetWidth();
    double graph_height = height * (1 - (2*GRAPH_PADDING_Y));
    int binNum = world.GetUpdate()/UPDATE_HIST;

    int pop_size = 0;
    int i = 0;
    int mut_total = 0; 
    int par_total = 0; 
    int highly_mut_total = 0; 
    int highly_par_total = 0;     
    int neu_total = 0;     
    for (int x = 0; x < config.GRID_X(); x++){
            for (int y = 0; y < config.GRID_Y(); y++){
                //hosts
                double val = p[i]->GetIntVal();
                if(val >= 0.6){
                  highly_mut_total += 1;
                } else if (val < 0.6 && val >= 0.2){
                  mut_total+=1;
                } else if (val < 0.2 && val >= -0.2){
                  neu_total+=1;
                } else if (val < -0.2 && val >= -0.7){
                  par_total+=1;
                } else{
                  highly_par_total+=1; 
                }
                pop_size++;
                i++;
            }
    }

    std::string highly_mut_color = matchColor(1.0);
    std::string mut_color = matchColor(0.59);    
    std::string neu_color = matchColor(0.19);
    std::string par_color = matchColor(-0.21);
    std::string highly_par_color = matchColor(-0.61);    
    int binWidth = (width-(2*GRAPH_PADDING_X))/(1000/UPDATE_HIST);
    double highMutEndPoint = height*GRAPH_PADDING_Y + graph_height*highly_mut_total/pop_size;
    double mutEndPoint = highMutEndPoint + graph_height*mut_total/pop_size;
    double neuEndPoint = mutEndPoint + graph_height*neu_total/pop_size;
    double parEndPoint = neuEndPoint + graph_height*par_total/pop_size;
    //int highParBeginPoint = (height*0.7) + parBeginPoint;
    can.Rect(binNum*binWidth + GRAPH_PADDING_X, height*GRAPH_PADDING_Y, binWidth, graph_height*highly_mut_total/pop_size, highly_mut_color); 
    can.Rect(binNum*binWidth + GRAPH_PADDING_X, highMutEndPoint, binWidth, graph_height*mut_total/pop_size, mut_color);   
    can.Rect(binNum*binWidth + GRAPH_PADDING_X, mutEndPoint, binWidth, graph_height*neu_total/pop_size, neu_color);   
    can.Rect(binNum*binWidth + GRAPH_PADDING_X, neuEndPoint, binWidth, graph_height*par_total/pop_size, par_color);   
    can.Rect(binNum*binWidth + GRAPH_PADDING_X, parEndPoint, binWidth, graph_height*highly_par_total/pop_size, highly_par_color);
  }

  /**
   * Input: The canvas being used. 
   * 
   * Output: None
   * 
   * Purpose: To draw the petri dish of basteria and phage. 
   */
  // now draw a virtual petri dish with coordinate offset from the left frame
  void drawPetriDish(UI::Canvas & can){
        int i = 0;
        num_mutualistic = 0;
        num_parasitic = 0;
        //bool temp_passed = true;
        for (int x = 0; x < config.GRID_X(); x++){
            for (int y = 0; y < config.GRID_Y(); y++){
                emp::vector<emp::Ptr<Organism>>& syms = p[i]->GetSymbionts(); // retrieve all syms for this host (assume only 1 sym for each host)
                // color setting for host and symbiont

                std::string color_host = matchColor(p[i]->GetIntVal());
                // Draw host rect and symbiont dot
                can.Rect(x * RECT_WIDTH, y * RECT_WIDTH, RECT_WIDTH, RECT_WIDTH, color_host, "black");
                int radius = RECT_WIDTH / 3;
                if(syms.size() == 1) {
                  std::string color_sym = matchColor(syms[0]->GetIntVal());
                  // while drawing, test whether every organism is mutualistic
                  if (syms[0]->GetIntVal() <= 0) num_parasitic++;
                  else num_mutualistic++;
                  can.Circle(x * RECT_WIDTH + RECT_WIDTH/2, y * RECT_WIDTH + RECT_WIDTH/2, radius, color_sym, "black");
                }
                i++;

            }
        }
        //passed = temp_passed; // update passed
  }

  // match the interaction value to colors, assuming that -1.0 <= intVal <= 1.0.
  // The antogonistic have light colors, and the cooperative have dark, brownish colors.


  /**
   * Input: The double representing symbiont or host's interaction value 
   * 
   * Output: The string representing the hex value for the color of the organism. 
   * 
   * Purpose: To determine the color that an organism should be, given its
   * interaction value. 
   */  
  std::string matchColor(double intVal){
    if ((-1.0 <= intVal) && (intVal < -0.9)) return "#EFFDF0";
    else if ((-0.9 <= intVal) && (intVal < -0.8)) return "#D4FFDD";
    else if ((-0.8 <= intVal) && (intVal < -0.7)) return "#BBFFDB";
    else if ((-0.7 <= intVal) && (intVal < -0.6)) return "#B2FCE3";
    else if ((-0.6 <= intVal) && (intVal < -0.5)) return "#96FFF7";
    else if ((-0.5 <= intVal) && (intVal < -0.4)) return "#86E9FE";
    else if ((-0.4 <= intVal) && (intVal < -0.3)) return "#6FC4FE";
    else if ((-0.3 <= intVal) && (intVal < -0.2)) return "#5E8EFF";
    else if ((-0.2 <= intVal) && (intVal < -0.1)) return "#4755FF";
    else if ((-0.1 <= intVal) && (intVal < 0.0)) return "#5731FD";
    else if ((0.0 <= intVal) && (intVal < 0.1)) return "#7B1DFF";
    else if ((0.1 <= intVal) && (intVal < 0.2)) return "#AB08FF";
    else if ((0.2 <= intVal) && (intVal < 0.3)) return "#E401E7";
    else if ((0.3 <= intVal) && (intVal < 0.4)) return "#D506AD";
    else if ((0.4 <= intVal) && (intVal < 0.5)) return "#CD0778";
    else if ((0.5 <= intVal) && (intVal < 0.6)) return "#B50142";
    else if ((0.6 <= intVal) && (intVal < 0.7)) return "#A7000F";
    else if ((0.7 <= intVal) && (intVal < 0.8)) return "#891901";
    else if ((0.8 <= intVal) && (intVal < 0.9)) return "#7D3002";
    else return "#673F03";
  }

  /**
   * Input: The canvas being used. 
   * 
   * Output: None
   * 
   * Purpose: To draw a dynamic graph of average interaction values 
   */
  void drawHostIntValGraph(UI::Canvas & can){
    double height = can.GetHeight();
    double graph_width = can.GetWidth()-(2*GRAPH_PADDING_X);
    //double x_step = graph_width/config.UPDATES();
    double x_step = graph_width/1000;

    int pop_size = p.size();
    double int_val_total = 0;
    int i = 0;
    for (int x = 0; x < config.GRID_X(); x++){
            for (int y = 0; y < config.GRID_Y(); y++){
                //hosts
                int_val_total += p[i]->GetIntVal();
                i++;
            }
    }
    double avg_int_val = int_val_total/pop_size;
    std::string color = matchColor(avg_int_val);

    double y = (height/2) - ((1 - (2*GRAPH_PADDING_Y)) * avg_int_val * (height/2));
    double x = GRAPH_PADDING_X + (world.GetUpdate() * x_step);

    can.Circle(x, y, 1, color, color);
  }

  void drawSymIntValGraph(UI::Canvas & can){
    double height = can.GetHeight();
    double graph_width = can.GetWidth()-(2*GRAPH_PADDING_X);
    //double x_step = graph_width/config.UPDATES();
    double x_step = graph_width/1000;

    int pop_size = 0;
    double int_val_total = 0;
    int i = 0;

    for (int x = 0; x < config.GRID_X(); x++){
            for (int y = 0; y < config.GRID_Y(); y++){
                //hosts
                emp::vector<emp::Ptr<Organism>> syms = p[i]->GetSymbionts();
                for (int j = 0; j  < syms.size(); j++){
                  int_val_total+= syms[j]->GetIntVal();
                  pop_size++;
                }
                i++;
            }
    }
    double avg_int_val = int_val_total/pop_size;
    std::string color = matchColor(avg_int_val);

    double y = (height/2) - ((1 - (2*GRAPH_PADDING_Y)) * avg_int_val * (height/2));
    double x = GRAPH_PADDING_X + (world.GetUpdate() * x_step);

    can.Circle(x, y, 1, color, color);
  }

  /**
   * Input: None
   * 
   * Output: None
   * 
   * Purpose: To update the frame displayed of the current 
   * world state. 
   */
  void DoFrame() {

    if (world.GetUpdate() == config.UPDATES() && GetActive()) {
        ToggleActive();
    } else {
      mycanvas = animation.Canvas("can"); // get canvas by id
      mycanvas.Clear();

      host_graph_canvas = graphs.Canvas("host_graph"); //get canvas by id
      host_histogram_canvas = graphs.Canvas("host_histogram");
      sym_graph_canvas = graphs.Canvas("sym_graph");
      sym_histogram_canvas = graphs.Canvas("sym_histogram");
      // Update world and draw the new petri dish
      world.Update();
      p = world.GetPop();
      drawPetriDish(mycanvas);

      //Update live graph here
      drawHostIntValGraph(host_graph_canvas);
      drawSymIntValGraph(sym_graph_canvas);

      if (world.GetUpdate() % UPDATE_HIST == 0 ||world.GetUpdate() == 2){
        drawSymStackedHist(sym_histogram_canvas);
        drawHostStackedHist(host_histogram_canvas);
      }
    }
  }
};
#endif