#ifndef SYM_CONFIG_PANEL_H
#define SYM_CONFIG_PANEL_H

#include "../../Empirical/include/emp/prefab/ConfigPanel.hpp"
#include "../../Empirical/include/emp/config/config.hpp"

class SymConfigPanel : public emp::prefab::ConfigPanel{
    protected:

    public:
        SymConfigPanel(emp::Config & config, bool open = true, const std::string & div_name = "") : ConfigPanel(config, open, div_name){

        }

};

#endif