fmap = open("pos_out315.txt")
mp = {}
while True:
	line = fmap.readline()
	if not line:
		break
	vec = line.split()
	mp[vec[0]]=vec[1]
	if float(vec[1])>=20:
		print vec[0]

# fres = open("pos_out051.txt")
# while True:
# 	line = fres.readline()
# 	if not line:
# 		break
# 	vec = line.split()
# 	if float(vec[1])>=4:
# 		print mp[vec[0]]