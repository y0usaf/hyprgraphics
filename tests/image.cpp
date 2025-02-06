#include <print>
#include <format>
#include <filesystem>
#include <hyprgraphics/image/Image.hpp>
#include <hyprgraphics/image/utils/ImageValidator.hpp>
#include "shared.hpp"

using namespace Hyprgraphics;

bool tryLoadImage(const std::string& path) {
    // Instead of creating a CImage directly, we now use the ImageValidator.
    auto validationResult = ImageUtils::validateImage(path);
    if (!validationResult) {
        std::println("Failed to load {}: {}", path, validationResult.error());
        return false;
    }
    auto pCairoSurface = validationResult.value();
    std::println("Loaded {} successfully: Image is {}x{}",
                 path,
                 pCairoSurface->size().x,
                 pCairoSurface->size().y);

    const auto TEST_DIR = std::filesystem::current_path().string() + "/test_output";

    // write the image out for inspection
    if (!std::filesystem::exists(TEST_DIR))
        std::filesystem::create_directory(TEST_DIR);

    // Since MIME is no longer available from CImage, we name the file based on its dimensions.
    std::string name = std::to_string(pCairoSurface->size().x) + "x" + std::to_string(pCairoSurface->size().y);
    return cairo_surface_write_to_png(pCairoSurface->cairo(), (TEST_DIR + "/" + name + ".png").c_str()) == CAIRO_STATUS_SUCCESS;
}

int main(int argc, char** argv, char** envp) {
    int ret = 0;

    for (auto& file : std::filesystem::directory_iterator("./resource/images/")) {
        if (!file.is_regular_file())
            continue;
        auto expectation = true;
#ifndef JXL_FOUND
        if (file.path().filename() == "hyprland.jxl")
            expectation = false;
#endif
        EXPECT(tryLoadImage(file.path().string()), expectation);
    }

    return ret;
}
