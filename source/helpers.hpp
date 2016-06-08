#pragma once

#include "interface.hpp"

namespace iris {
namespace helpers {

    bool valueToString(JSContext& context, jsval& input, std::string& output);

    bool stringToValue(JSContext& context, const std::string& input, jsval& target);

};
};