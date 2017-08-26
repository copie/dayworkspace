string = input()
d=['ling','yi','er','san','si','wu','liu','qi','ba','jiu']
print(" ".join(map(lambda x: d[int(x)], str(sum(map(int, string))))))
