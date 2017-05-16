input_list = open('input_list.txt', 'w')
output_list = open('output_list.txt', 'w')
truth_list = open('truth_list.txt', 'w')

input_base = "D:\\\\\\\\Documents\\\\project2_dataset\\\\images\\\\"
output_base = "D:\\\\\\\\Documents\\\\project2_dataset\\\\results\\\\"
truth_base = "D:\\\\\\\\Documents\\\\project2_dataset\\\\gt\\\\"

for i in range(1, 301):
    img = '%03d.jpg\n' % (i)
    input_list.write(input_base + img)
    output_list.write(output_base + img)
    truth_list.write(truth_base + img)

input_list.close()
output_list.close()
truth_list.close()
