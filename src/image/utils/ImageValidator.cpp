#include <hyprgraphics/image/utils/ImageValidator.hpp>
#include <hyprgraphics/image/Image.hpp>

namespace Hyprgraphics {
namespace ImageUtils {

std::expected<Hyprutils::Memory::CSharedPointer<CCairoSurface>, std::string> validateImage(const std::string& path) {
    // Create an image using the CImage loader.
    CImage image(path);

    // If the image did not load successfully, return the error.
    if (!image.success())
        return std::unexpected(image.getError());

    // Retrieve the Cairo surface wrapper.
    auto pCairoSurface = image.cairoSurface();
    if (!pCairoSurface)
        return std::unexpected("Image surface is null");

    // Verify that the underlying Cairo surface status is OK.
    cairo_surface_t* surface = pCairoSurface->cairo();
    if (cairo_surface_status(surface) != CAIRO_STATUS_SUCCESS)
        return std::unexpected(std::string("Cairo surface error: ") +
                               cairo_status_to_string(cairo_surface_status(surface)));

    return pCairoSurface;
}

} // namespace ImageUtils
} // namespace Hyprgraphics 