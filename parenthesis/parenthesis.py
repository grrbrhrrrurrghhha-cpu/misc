code = input()
error = False
while normal:
	normal = False
	balance = 0
	start = 0
	pairs = 0
	a = ""
	b = ""
	for i, c in enumerate(code):
		if c == "(":
			balance += 1
		elif c == ")":
			balance -= 1
		else:
			error = True
			break
		if balance < 0:
			error = True
			break
		elif balance == 0:
			if pairs == 0:
				a = code[start+1:i]
			else:
				b = code[start+1:i]
				b = b.replace("()", a)
				code = b + code[i+1:]
				normal = True
				break
			start = i + 1
			pairs += 1
	if balance != 0:
		error = True
	if error:
		print("?")
		break
	if not normal:
		print("Result: ")
	print(code)
