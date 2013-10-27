import Image
import math

def main(): ##MAKE SURE TO ADD VARIABLE SIZE IMAGES
	img = Image.new("RGB",(640,480),(0,0,0))
	pix = img.load()
	w,h = img.size
	f = open("render_output","r")
	
	for line in f:
		nums = []
		nums = line.split(" ")
		pix[int(nums[0]),int(nums[1])] = int(nums[2]),int(nums[3]),int(nums[4])
		
	img.show()
	img.save("output.png","PNG")
	
		
	
	
main()