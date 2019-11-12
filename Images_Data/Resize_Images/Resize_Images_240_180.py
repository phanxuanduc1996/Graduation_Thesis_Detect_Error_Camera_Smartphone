import os
import cv2

folder_path = "D:/DATA/CODE/GraduationProject/Original_Images/"
save_path = "D:/DATA/CODE/GraduationProject/Resize_Images/"
if not os.path.exists(save_path):
    os.makedirs(save_path)

# files = [os.path.join(folder_path, f) for f in os.listdir(folder_path) if os.path.isfile(os.path.join(folder_path, f))]
# print files

for path, subdirs, files in os.walk(folder_path):
    for name in files:
        file = os.path.join(path, name)
        print (file)
        image = cv2.imread(file)
        image = cv2.resize(image, (240, 180))
        file = file.replace(folder_path, save_path)
        if not os.path.exists(os.path.dirname(file)):
            os.makedirs(os.path.dirname(file))
        cv2.imwrite(file, image)
        # cv2.imshow('Video', image)
        # cv2.waitKey(500)

