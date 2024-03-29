import tensorflow as tf
import os
#os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
import numpy as np
import os
import glob
import cv2
import sys
import argparse


# First, pass the path of the image
files = []
for file in glob.glob("img_test/ok/*.jpg"):
    files.append(file)
correct_vals = np.zeros((1, 2))
#filename = image_path +'/' +'cat.372.jpg'
num_channels = 3
name_classes = ['NG', 'OK']
sess = tf.Session()
saver = tf.train.import_meta_graph('save/Flare.meta')

saver.restore(sess, tf.train.latest_checkpoint('save/'))
graph = tf.get_default_graph()

y_pred = graph.get_tensor_by_name("y_pred:0")

x = graph.get_tensor_by_name("x:0")
y_true = graph.get_tensor_by_name("y_true:0")
# gte number of classs
y_test_images = np.zeros((1, len(os.listdir('img_train'))))

TP = 0
FP = 0
FN = 0
TN = 0

for filename in files:
    images = []
    image = cv2.imread(filename)
    image = cv2.resize(image, (224, 224), 0, 0, cv2.INTER_LINEAR)
    images.append(image)
    images = np.array(images, dtype=np.uint8)
    images = images.astype('float32')
    images = np.multiply(images, 1.0/255.0)
    x_batch = images.reshape(1, 224, 224, num_channels)
    feed_dict_testing = {x: x_batch, y_true: y_test_images}
    result = sess.run(y_pred, feed_dict=feed_dict_testing)
    print(result, end=" ")
    fn = str(filename)
    li = fn.split("\\")
    print(li[1], end=" ")
    if(result[0][1] > 0.5):
        TP += 1
        FN += 1
        print('OK')
    else:
        FP += 1
        TN += 1
        print('NG')

print("Total = ", len(files), "  TP=", TP, "  FP=", FP, " TN=", TN, " FN=", FN)
