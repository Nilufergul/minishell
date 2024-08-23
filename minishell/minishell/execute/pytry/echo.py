

def echo(s):
	ans = 0
	expect = 1
	n_count = 0
	for i in range(len(s)):
		if expect == 1:
			if s[i] == "-":
				expect = 2
			else:
				return ans
			n_count = 0
		elif expect == 2:
			if s[i] == "n":
				n_count += 1
				expect = 3
			elif s[i] == " ":
				ans = i + 1
				return ans
			else:
				return ans
		else:
			if s[i] == " ":
				ans = i + 1
				expect = 1
			elif s[i] == "-" and n_count == 1:
				expect = 2
			elif s[i] != "n":
				return ans
			n_count = 0
	return ans

def yaz(s):
	ind = echo(s)
	print(s[ind:])

yaz("-n selman")
yaz("-n -n selman")
yaz("-n-n-n selman")
yaz("-nnnnnn selman")
yaz("selman")
yaz("-nnnm selman")
yaz("-m -n selman")
yaz("-n -m selman")
yaz("-nnnnnn-n selman")
yaz("--nnnnnn-n selman")
yaz("- selman")


