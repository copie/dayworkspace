import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt


def add_layer(inputs, in_size, out_size,n_layer,actvation_function=None):

    layer_name = 'layer%s'% n_layer
    with tf.name_scope(layer_name):
        with tf.name_scope('weights'):
            Weights = tf.Variable(tf.random_normal([in_size, out_size]),name='W')
            tf.summary.histogram(layer_name+'/weights',Weights)
        with tf.name_scope('biases'):
            biases = tf.Variable(tf.zeros([1, out_size]) + 0.1,'biases')
            tf.summary.histogram(layer_name+'/biases',biases)
        with tf.name_scope('Wx_plus_b'):
            Wx_plus_b = tf.matmul(inputs, Weights) + biases

        if actvation_function is None:
            outputs = Wx_plus_b
        else:
            outputs = actvation_function(Wx_plus_b)
        tf.summary.histogram(layer_name+'/outputs',outputs)
        return outputs


x_data = np.linspace(-2, 2, 1000)[:, np.newaxis]
noise = np.random.normal(-0.1, 0.1, x_data.shape)
y_data = np.square(x_data) - 0.5 + noise

with tf.name_scope('inputs'):
    xs = tf.placeholder(tf.float32, [None, 1],name='x_input')
    ys = tf.placeholder(tf.float32, [None, 1],name='y_input')

l1 = add_layer(xs, 1, 10,n_layer=1, actvation_function=tf.nn.relu)
predition = add_layer(l1, 10, 1,n_layer =2, actvation_function=None)
with tf.name_scope('loss'):
    loss = tf.reduce_mean(tf.reduce_sum(
        tf.square(ys - predition), reduction_indices=[1]),name='Loss')
    tf.summary.scalar('loss',loss)
with tf.name_scope('train'):
    train_step = tf.train.GradientDescentOptimizer(0.1).minimize(loss)

init = tf.initialize_all_variables()

sess = tf.Session()
merged = tf.summary.merge_all()
write = tf.summary.FileWriter('logs/',sess.graph)
sess.run(init)

fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
ax.scatter(x_data, y_data)
plt.ion()
plt.show()

for i in range(1000):
    sess.run(train_step, feed_dict={xs: x_data, ys: y_data})
    if i % 50 == 0:
        # print(sess.run(loss, feed_dict={xs: x_data, ys: y_data}))
        result = sess.run(merged,feed_dict={xs:x_data,ys:y_data})
        write.add_summary(result,i)
        predition_value = sess.run(predition, feed_dict={xs: x_data})
        try:
            ax.lines.remove(lines[0])
        except Exception:
            pass
        # lines = ax.plot(x_data, predition_value, 'r-', lw=1)
        # plt.pause(0.5)
