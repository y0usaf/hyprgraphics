#pragma once

#include <string>
#include <expected>
#include <hyprutils/memory/SharedPtr.hpp>
#include "../../cairo/CairoSurface.hpp"

namespace Hyprgraphics {
namespace ImageUtils {

// Attempts to load and validate an image at the given path.
// On success, returns a shared pointer wrapping the underlying Cairo surface.
// Otherwise, returns an error message.
std::expected<Hyprutils::Memory::CSharedPointer<CCairoSurface>, std::string> validateImage(const std::string& path);

} // namespace ImageUtils
} // namespace Hyprgraphics 