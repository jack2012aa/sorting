import random

def selection_sorts(alist):
    '''
    從list的開頭往後讀，把讀到最小的資料放到最前面，再重下一個位置開始讀
    '''

    wall = 0
    while wall < len(alist):
        min = alist[wall]
        min_index = wall
        for i in range(wall, len(alist)):
            if alist[i] < min:
                min = alist[i]
                min_index = i
        trans = alist[wall]
        alist[wall] = min
        alist[min_index] = trans
        wall += 1

    return alist

def bubble_sorts(alist):
    '''
    從右往左一次檢查兩個數字，如果右邊的數字較小就替換到左邊
	'''
    wall = 0
    while wall < len(alist):
        for i in range(len(alist) - 1, wall, -1):
            if alist[i] < alist[i-1]:
                trans = alist[i]
                alist[i] = alist[i-1]
                alist[i-1] = trans
        wall += 1

    return alist

def insertion_sorts(alist):
    '''
    把資料從牆右側的第一個數字抓到左側排列好的序列中，插入正確大小的位置
    '''
    wall = 1
    while wall < len(alist):
        inserted_num = alist[wall]
        for i in range(wall):
            if inserted_num <= alist[i]:
                for j in range(wall, i, -1):
                    alist[j] = alist[j - 1]
                alist[i] = inserted_num
                break
        wall += 1
    
    return alist

def list_generator(alist, length, max):
    '''
    隨機生成測試用的list
    '''
    for i in range(length):
        alist.append(random.randrange(-max, max))
    print("Test list: ", alist)

    return alist

def test_be_sorted(alist):
    '''
    測試是否有正確排序
    '''
    for i in range(len(alist) - 1):
        if alist[i] > alist[i + 1]:
            print(alist, "\nThis list has not been sorted!")
            return 0
    print(alist, "\nThis list has been sorted.")





test_list = []
test_list = list_generator(test_list, 300, 1000)

print("\n============================\n")
selection_sorts_result = selection_sorts(test_list.copy())            
test_be_sorted(selection_sorts_result)

print("\n============================\n")
bubble_sorts_result = bubble_sorts(test_list.copy())
test_be_sorted(bubble_sorts_result)

print("\n============================\n")
insertion_sorts_result = insertion_sorts(test_list.copy())
test_be_sorted(insertion_sorts_result)