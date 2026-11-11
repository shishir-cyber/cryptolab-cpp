#pragma once
#include <string_view>

namespace cryptolab {

/// Library version as "MAJOR.MINOR.PATCH".
std::string_view version() noexcept;

}  // namespace cryptolab
