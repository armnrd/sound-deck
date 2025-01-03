/**
 * @file config.hpp
 * @brief ${DESCRIPTION}
 *
 * @author Arindam
 * @date 11/11/2024
 */

#ifndef SOUND_DECK_CONFIG_HPP
#define SOUND_DECK_CONFIG_HPP

#include <string>

// Structure to hold the configuration data
struct Config {
    std::string app_name;
    int version;
    std::string host;
    int port;
};

Config load_config(const std::string& filename);

void save_config(const std::string& filename, const Config& cfg);

#endif //SOUND_DECK_CONFIG_HPP
