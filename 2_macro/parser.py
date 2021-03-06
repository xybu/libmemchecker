log_file = open("libmemchecker.txt", "r")
target = log_file.read()
log_file.close()

records = {}
memcount = 0

lines = target.replace("(nil)", "0x0").split("\n")
for record_str in lines:
	# print record_str
	fields = record_str.split("\t")
	if fields[0] == "+":	# +	%lu	%p	func
		records[str(fields[2])] = long(fields[1])
		memcount += int(fields[1])
	elif fields[0] == "~":	# ~	%lu	%p_prev	%p_new	realloc
		if fields[2] != "0x0": # to handle ptr = realloc(NULL, size_t)
			memcount -= records[str(fields[2])]
			del records[str(fields[2])]
		records[str(fields[3])] = long(fields[1])
		memcount += int(fields[1])
	elif fields[0] == "-":	# -	%p
		if fields[1] != "0x0" and fields[1] in records:
			memcount -= records[str(fields[1])]
			del records[str(fields[1])]
	else:
		pass

print str(records)

print "Remaining bytes: " + str(memcount)
