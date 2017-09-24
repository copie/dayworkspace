# import tensorflow as tf
# import numpy as np

# # create data
# x_data = np.random.rand(100).astype(np.float32)
# y_data = x_data * 0.1 + 0.3

# # create tensorflow structure start #

# Weights = tf.Variable(tf.random_uniform([1], -10, 10))
# biase = tf.Variable(tf.zeros([1]))

# y = x_data * Weights + biase

# loss = tf.reduce_mean(tf.square(y-y_data))
# optimizer = tf.train.GradientDescentOptimizer(0.5)
# train = optimizer.minimize(loss)

# init = tf.initialize_all_variables()
# # create tensorflow strcture end #

# sess = tf.Session()
# sess.run(init)

# for step in range(300):
#     sess.run(train)
#     if step%20 == 0:
#         print(sess.run(Weights),sess.run(biase))

import tensorflow as tf
import numpy as np

# create data
x_data = np.random.rand(100000).astype(np.float128)
y_data = 9.999999 * x_data**3 + 5.88788888

# create tensorflow structure start #

Weights = tf.Variable(tf.zeros([1]))
biase = tf.Variable(tf.zeros([1]))

y = Weights * x_data**3 + biase

loss = tf.reduce_mean(tf.square(y - y_data))
optimizer = tf.train.GradientDescentOptimizer(0.5)
train = optimizer.minimize(loss)

init = tf.initialize_all_variables()
# create tensorflow structure end #

sess = tf.Session()
sess.run(init)

for temp in range(10000):
    sess.run(train)
    if temp % 200 == 0:
        print(temp, sess.run(Weights), sess.run(biase))
