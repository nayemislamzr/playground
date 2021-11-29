def solve(numbers):
    m_length = [1]*len(numbers)
    for i in range(0,len(numbers)):
        for j in range (0,i):
            if numbers[i] > numbers[j]:
                m_length[i] = max(m_length[i],m_length[j]+1)
    return m_length


numbers = []
total_numbers = int(input("Enter total numbers : "))
for i in range(0, total_numbers):
    numbers.append(int(input()))

print(solve(numbers))

