import tensorflow as tf

matrix1 = tf.constant([[3, 3]])
matrix2 = tf.constant([[4],[4]])

product = tf.matmul(matrix1,matrix2)   # 矩阵乘法 np.dot()

with tf.Session() as sess:
    result = sess.run(product)
    print(result)
