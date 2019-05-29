import os

def main():
	files = os.listdir("./")
	for i in files:
		if i.endswith(".cpp") and i != "lexeme.cpp" and i != "main.cpp":
			# print(i.replace(".cpp",""))
			writeHeaders(i.replace(".cpp",""))

def getTypes():
	stuff=[]
	f = open("help.txt",'rt')
	for i in f:
		item = i.replace('\n',"").replace('\t',"").replace(",","")
		stuff.append(item)
	f.close()
	stuff = sorted(stuff)
	f = open("output.txt",'wt')
	for i in stuff:
		f.write(i+",\n")
	f.write("\n")

	count = 0
	for i in stuff:
		f.write("case "+str(count)+": return \""+i+"\";\n")
		count+=1
	f.close()

def writeHeaders(file):
	stuff=[]
	f = open(file+".cpp",'rt')
	f2 = open(file+".h",'wt')
	f2.write("#ifndef "+file+"_\n")
	f2.write("#define "+file+"_\n")
	for i in f:
		if ("Lexeme* " in i or "bool " in i or "void " in i or "string " in i or "int " in i) and "{" in i:
			i=i.replace("{",";").replace(") ",")")
			f2.write(i)
			stuff.append(i)
	f.close()
	f2.write("#endif\n")
	f2.close()

main()