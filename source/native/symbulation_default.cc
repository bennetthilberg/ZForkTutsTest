#include "../default_mode/SymWorld.h"
#include "../default_mode/Symbiont.h"
#include "../default_mode/Host.h"
#include "../default_mode/WorldSetup.cc"
#include "../../Empirical/include/emp/config/ArgManager.hpp"
#include <iostream>
#include "../ConfigSetup.h"

using namespace std;

// This is the main function for the NATIVE version of this project.

int symbulation_main(int argc, char * argv[])
{
  SymConfigBase config;

  bool success = config.Read("SymSettings.cfg");
  if(!success) {
    std::cout << "You didn't have a SymSettings.cfg, so one is being written, please try again" << std::endl;
    config.Write("SymSettings.cfg");
  }

  auto args = emp::cl::ArgManager(argc, argv);
  if (args.ProcessConfigOptions(config, std::cout, "SymSettings.cfg") == false) {
    cerr << "There was a problem in processing the options file." << endl;
    exit(1);
  }
  if (args.TestUnknown() == false) {
    cerr << "Leftover args no good." << endl;
    exit(1);
  }

  config.Write(std::cout);
  emp::Random random(config.SEED());

  SymWorld world(random);


  int TIMING_REPEAT = config.DATA_INT();


  //Set up files
  //world.SetupPopulationFile().SetTimingRepeat(TIMING_REPEAT);

  std::string file_ending = "_SEED"+std::to_string(config.SEED())+".data";

  world.SetupHostIntValFile(config.FILE_PATH()+"HostVals"+config.FILE_NAME()+file_ending).SetTimingRepeat(TIMING_REPEAT);
  world.SetupSymIntValFile(config.FILE_PATH()+"SymVals"+config.FILE_NAME()+file_ending).SetTimingRepeat(TIMING_REPEAT);
  
  if(config.FREE_LIVING_SYMS() == 1){
    world.SetUpFreeLivingSymFile(config.FILE_PATH()+"FreeLivingSyms_"+config.FILE_NAME()+file_ending).SetTimingRepeat(TIMING_REPEAT);
  }

  worldSetup(&world, &config);
  int numupdates = config.UPDATES();

  //Loop through updates
  for (int i = 0; i < numupdates; i++) {
    if((i%TIMING_REPEAT)==0) {
      cout <<"Update: "<< i << endl;
      cout.flush();
    }
    world.Update();
  }

  return 0;
}

/*
This definition guard prevents main from being defined twice during testing.
In testing, Catch will define a main function which will initiate tests
(including testing the symbulation_main function above).
*/
#ifndef CATCH_CONFIG_MAIN
int main(int argc, char * argv[]) {
  return symbulation_main(argc, argv);
}
#endif
