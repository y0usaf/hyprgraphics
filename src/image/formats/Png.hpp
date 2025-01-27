#pragma once

#include <cairo/cairo.h>
#include <string>
#include <expected>

namespace PNG {
    std::expected<cairo_surface_t*, std::string> createSurfaceFromPNG(const std::string&);
};