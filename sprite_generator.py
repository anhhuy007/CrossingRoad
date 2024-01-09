from PIL import Image

def closest_color(rgb):
    """
    Converts an RGB color to the closest 16-indexed color.
    """
    # colors = [
    #     (0, 0, 0), (0, 0, 255), (6, 85, 53), (255, 215, 0),
    #     (255, 0, 0), (128, 0, 128), (165, 42, 42), (192, 192, 192),
    #     (255, 165, 0), (0, 255, 255), (148, 225, 147), (255, 255, 0),
    #     (255, 115, 115), (255, 192, 203), (183, 84, 84), (255, 255, 255)
    # ]

    # ---- MENU ----
    # colors = [
    #     (0, 0, 0), (255, 255, 255), (168, 201, 205), (214, 229, 230),  
    #     (128, 177, 177),  (15, 47, 67), (245, 211, 88), (69, 56, 10),
    #     (187, 213, 245), (118, 151, 201), (246, 135, 151), (70, 70, 70),
    #     (65, 39, 42), (255, 59, 69),  (176, 40, 49), (77, 18, 30)
    # ]

    # ---- STREET MAP ----    
    # colors = [
    #     (0, 0, 0), (255, 255, 255), (174, 222, 102), (159, 204, 92),
    #     (110, 184, 46), (12, 67, 57), (127, 137, 173),  (96, 109, 138),
    #     (72, 78, 94), (113, 215, 255), (126, 74, 76), (255, 112, 51),
	# 	(65, 39, 42), (255, 59, 69), (176, 40, 49), (77, 18, 30)
    # ]

    # ---- WINTER MAP ----    
    colors = [
        (0, 0, 0), (255, 251, 255), (174, 222, 102), (159, 204, 92),
        (110, 184, 46), (12, 67, 57), (127, 137, 173),  (96, 109, 138),
        (72, 78, 94), (113, 215, 255), (126, 74, 76), (255, 112, 51),
		(65, 39, 42), (255, 59, 69), (176, 40, 49), (77, 18, 30)
    ]


    differences = []
    for color in colors:
        r_diff = abs(rgb[0] - color[0])
        g_diff = abs(rgb[1] - color[1])
        b_diff = abs(rgb[2] - color[2])
        differences.append(r_diff + g_diff + b_diff)
    return differences.index(min(differences))


# Open the PNG file and load the RGB color matrix
fileName = 'space'
outFile = 'Space' + '.sprite'
sourcePath = "C:\\Users\\ADMIN\\Downloads\\CrossingRoad Images\\"
destinationPath = "D:\\Crossing Road\\CrossingRoad\\CrossingRoad\\alphabet\\normal"

# for i in range(0, 10):
#     image = Image.open(sourcePath + fileName + str(i) + '.png')
#     rgbMatrix = image.convert('RGBA')

#     # Get the dimensions of the image
#     width, height = image.size

#     try:
#         # Open the output file for writing
#         with open(destinationPath + str(i) + '.sprite', 'w') as outputFile:
#             outputFile.write(f"{width} {height}\n")
#             # Write the coordinate and color information to the output file
#             for y in range(height):
#                 for x in range(width):
#                     r, g, b, a = rgbMatrix.getpixel((x, y))
#                     if a < 255:
#                         outputFile.write(f"{y} {x} -1\n")
#                     else:
#                         closest_index = closest_color((r, g, b))
#                         outputFile.write(f"{y} {x} {closest_index}\n")
#     except Exception as e:
#         print("Error: ", e)

image = Image.open(sourcePath + fileName + '.png')
rgbMatrix = image.convert('RGBA')

# Get the dimensions of the image
width, height = image.size

try:
    # Open the output file for writing
    with open(destinationPath + outFile, 'w') as outputFile:
        outputFile.write(f"{width} {height}\n")
        # Write the coordinate and color information to the output file
        for y in range(height):
            for x in range(width):
                r, g, b, a = rgbMatrix.getpixel((x, y))
                if a < 255:
                    outputFile.write(f"{y} {x} -1\n")
                else:
                    closest_index = closest_color((r, g, b))
                    outputFile.write(f"{y} {x} {closest_index}\n")
except Exception as e:
    print("Error: ", e)
