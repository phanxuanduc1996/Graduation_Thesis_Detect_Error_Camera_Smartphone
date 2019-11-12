import tensorflow as tf
import os
import dataset

tf.reset_default_graph()
n_classes = 2
batch_size = 128

# Prepare input data
classes = os.listdir('img_train')
num_classes = len(classes)

# 20% of the data will automatically be used for validation
validation_size = 0.2
#img_size = 128
num_channels = 3
train_path = 'img_train'

layer = ['W_conv1', 'b_conv1', 'W_conv2',
         'b_conv2', 'W_fc', 'b_fc', 'W_out', 'b_out']

session = tf.Session()
x = tf.placeholder(tf.float32, shape=[None, 80, 300, num_channels], name='x')

# labels
y_true = tf.placeholder(tf.float32, shape=[None, num_classes], name='y_true')
y_true_cls = tf.argmax(y_true, dimension=1)

data = dataset.read_train_sets(
    train_path, classes, validation_size=validation_size)


def conv2d(x, W):
    return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding='SAME')


def maxpool2d(x):
    return tf.nn.max_pool(x, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')


def conv_net(x, layer):
    weight = {
        'W_conv1': tf.Variable(tf.truncated_normal([5, 5, num_channels, 32], stddev=0.05)),
        'W_conv2': tf.Variable(tf.truncated_normal([5, 5, 32, 64], stddev=0.05)),
        'W_fc': tf.Variable(tf.truncated_normal([20*75*64, 1024], stddev=0.05)),
        'W_out': tf.Variable(tf.truncated_normal([1024, num_classes], stddev=0.05))
    }

    biases = {
        'b_conv1': tf.Variable(tf.constant(0.05, shape=[32])),
        'b_conv2': tf.Variable(tf.constant(0.05, shape=[64])),
        'b_fc': tf.Variable(tf.constant(0.05, shape=[1024])),
        'b_out': tf.Variable(tf.constant(0.05, shape=[num_classes]))
    }

    conv1 = tf.nn.relu(conv2d(x, weight['W_conv1'])+biases['b_conv1'])
    conv1 = maxpool2d(conv1)

    conv2 = tf.nn.relu(conv2d(conv1, weight['W_conv2'])+biases['b_conv2'])
    conv2 = maxpool2d(conv2)

    fc = tf.reshape(conv2, [-1, 20*75*64])
    fc = tf.nn.relu(tf.matmul(fc, weight['W_fc'])+biases['b_fc'])
    fc = tf.nn.dropout(fc, 0.8)

    out = tf.matmul(fc, weight['W_out'])+biases['b_out']

    return out


total_iterations = 0


def train(num_iteration):
    global total_iterations
    prediction = conv_net(x, layer)
    y_pred = tf.nn.softmax(prediction, name='y_pred')
    y_pred_cls = tf.argmax(y_pred, dimension=1)

    cost = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(
        logits=prediction, labels=y_true))
    optimizer = tf.train.AdamOptimizer(learning_rate=1e-4).minimize(cost)

    correct_prediction = tf.equal(y_pred_cls, y_true_cls)
    accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))

    session.run(tf.global_variables_initializer())

    saver = tf.train.Saver()
    session.run(tf.global_variables_initializer())
    for i in range(total_iterations,
                   total_iterations + num_iteration):

        x_batch, y_true_batch, _, cls_batch = data.train.next_batch(batch_size)
        x_valid_batch, y_valid_batch, _, valid_cls_batch = data.valid.next_batch(
            batch_size)

        feed_dict_tr = {x: x_batch,
                        y_true: y_true_batch}
        feed_dict_val = {x: x_valid_batch,
                         y_true: y_valid_batch}
        session.run(optimizer, feed_dict=feed_dict_tr)
        if i % int(data.train.num_examples / batch_size) == 0:
            val_loss = session.run(cost, feed_dict=feed_dict_val)
            acc = session.run(accuracy, feed_dict=feed_dict_tr)
            val_acc = session.run(accuracy, feed_dict=feed_dict_val)
            msg = "Training Epoch {0} --- Training Accuracy: {1:>6.1%}, Validation Accuracy: {2:>6.1%},  Validation Loss: {3:.3f}"
            print(msg.format(i + 1, acc, val_acc, val_loss))
            saver.save(session, 'save/Blur')
    total_iterations += num_iteration


train(num_iteration=50)
print("---------------------------------DONE MODEL--------------------------- ")
