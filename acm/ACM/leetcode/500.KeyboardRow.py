words = ["Hello", "Alaska", "Dad", "Peace"]
one = {'q','w','e','r','t','y','u','i','o','p','Q','W','E','R','T','Y','U','I','O','P'}
two = {'a','A','s','S','d','D','f','F','g','G','h','H','j','J','k','K','l','L'}
th ={'z','Z','x','X','c','C','v','V','b','B','n','N','m','M'}
words = list(zip(map(set,map(list,words)),words))
print ([w[1] for w in [ i for i in words if i[0] | one == one or i[0] | two == two or i[0] | th == th]])