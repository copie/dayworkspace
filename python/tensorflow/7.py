import tensorflow as tf

state = tf.Variable(0,name='counter')
one = tf.constant(1)

new_value = tf.add(state,one)
update = tf.assign(state,new_value) # state 的值 被 new_value 更新
init = tf.initialize_all_variables()

with tf.Session() as sess:
    sess.run(init)
    for _ in range(110):
        sess.run(update)
        print(sess.run(state))