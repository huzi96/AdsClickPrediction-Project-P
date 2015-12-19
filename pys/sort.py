from operator import itemgetter, attrgetter
cnt = 0
sort_list = []
while True:
	try:
		line = raw_input()
	except Exception, e:
		break
	vec = line.split()
	sort_list.append([vec[1], vec[0]])
	cnt+=1

sorted(sort_list, key=itemgetter(0,1)) 
for x in xrange(0,cnt):
	print sort_list[x][0]+' '+sort_list[x][1]