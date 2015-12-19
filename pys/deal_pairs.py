fout = open("id_out315.txt")
idoutmp = {}
while True:
	line = fout.readline()
	if not line:
		break
	vec = line.split()
	if float(vec[1])>2:
		idoutmp[vec[0]]=1

fmap = open("pairs.txt")
m_pairs = {}
while True:
	line = fmap.readline()
	if not line:
		break
	vec = line.split()
	if vec[1] in m_pairs:
		m_pairs[vec[1]].append(vec[0])
	else:
		m_pairs[vec[1]] = [vec[0]]

fmapp = open("sorted_pos.txt")
mpp = {}
while True:
	line = fmapp.readline()
	if not line:
		break
	vec = line.split()
	mpp[vec[0]]=vec[1]

fid = open("sorted_id.txt")
idpp = {}
while True:
	line = fid.readline()
	if not line:
		break
	vec = line.split()
	idpp[vec[0]]=vec[1]

outed = {}
while True:
	try:
		pos_index = raw_input()
	except:
		break
	# print mpp[pos_index],'\t',
	outed[mpp[pos_index]] = 1
	li = m_pairs[pos_index]
	for x in li:
		if x in idoutmp:
			print idpp[x],'\t',mpp[pos_index]
		
# full = open("pos_all.txt")
# while True:
# 	line = full.readline()
# 	if not line:
# 		break
# 	if line in outed:
# 		continue
# 	print line

			