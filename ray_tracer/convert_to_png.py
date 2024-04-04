from PIL import Image

def convert_ppm_to_png(ppm_file_path, png_file_path):
    """
    Converts a PPM image to a PNG image.

    :param ppm_file_path: The file path of the source PPM image.
    :param png_file_path: The desired file path for the output PNG image.
    """
    # Open the PPM image
    with Image.open(ppm_file_path) as img:
        # Convert and save the image in PNG format
        img.save(png_file_path, "PNG")

# Example usage
convert_ppm_to_png("sphere.ppm", "sphere_transformed.png")
