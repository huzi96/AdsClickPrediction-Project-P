cnt = 0
sort_list = []
while True:
	try:
		line = raw_input()
	except Exception, e:
		break
	vec = line.split()
	posi = float(vec[2])
	neg = float(vec[3])
	if neg >= posi*6.18:
            sort_list.append([vec[1], vec[0]])
            cnt += 1
for x in xrange(0,cnt):
	print sort_list[x][1]+'\t'+sort_list[x][0]
