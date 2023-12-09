def find_lowest_location_one(input_list):
    seeds_list = [int(number) for number in input_list[0][7:].split(' ')]
    print(seeds_list)
    i = 3
    while i < len(input_list):
        maps = list()
        while i < len(input_list) and (input_list[i] != ""):
            maps.append(list([int(number) for number in input_list[i].split(' ')]))
            i += 1
        mapped_seeds = {}
        temp_list = list()
        for seed in seeds_list:
            for map_line in maps:
                [dest_start, source_start, range_len] = map_line
                if seed in range(source_start, source_start + range_len):
                    mapped_seeds[seed] = seed + (dest_start - source_start)
                    break

        for seed in seeds_list:
            temp_list.append(mapped_seeds[seed] if seed in mapped_seeds else seed)
        seeds_list = temp_list
        i += 2
    return min(seeds_list)


def find_intersection_and_difference(range1, range2):
    start1, end1 = range1
    start2, end2 = range2

    # Find intersection
    intersection_start = max(start1, start2)
    intersection_end = min(end1, end2)

    if intersection_start < intersection_end:
        intersection = (intersection_start, intersection_end)
        differences = []

        # Calculate non-intersecting parts
        if start1 < intersection_start:
            differences.append((start1, intersection_start))
        if end1 > intersection_end:
            differences.append((intersection_end, end1))
        if start2 < intersection_start:
            differences.append((start2, intersection_start))
        if end2 > intersection_end:
            differences.append((intersection_end, end2))

        return intersection, differences
    else:
        # No intersection
        return None, [range1, range2]


def find_lowest_location(input_list):
    seeds_ranges = [int(number) for number in input_list[0][7:].split(' ')]
    print(seeds_ranges)
    i = 3
    seeds_list = list()
    for seed_j in range(0, len(seeds_ranges), 2):
        # Access elements using slicing
        a, b = seeds_ranges[seed_j:seed_j + 2]
        seeds_list.append(range(a, a + b))
    # print(len(seeds_list), seeds_list)
    while i < len(input_list):
        maps = list()
        while i < len(input_list) and (input_list[i] != ""):
            maps.append(list([int(number) for number in input_list[i].split(' ')]))
            i += 1
        mapped_seeds = {}
        not_mapped_seeds = list()
        temp_list = list()
        for seed in seeds_list:
            if seed.start in mapped_seeds:
                continue
            for map_line in maps:
                [dest_start, source_start, range_len] = map_line
                range1 = seed
                range2 = range(source_start, source_start + range_len)
                start1, end1 = range1.start, range1.stop
                start2, end2 = range2.start, range2.stop
                intersection_start = max(start1, start2)
                intersection_end = min(end1, end2)
                if intersection_start < intersection_end:
                    mapped_seeds[intersection_start] = range((intersection_start + (dest_start - source_start)),
                                                             (intersection_start + (
                                                                         dest_start - source_start) + (intersection_end-intersection_start)))
                    # Calculate non-intersecting parts
                    if start1 < intersection_start:
                        not_mapped_seeds.append(range(start1, intersection_start-1))
                    if end1 > intersection_end:
                        not_mapped_seeds.append(range(intersection_end, end1-1))
                    if start2 < intersection_start:
                        not_mapped_seeds.append(range(start2, intersection_start-1))
                    if end2 > intersection_end:
                        not_mapped_seeds.append(range(intersection_end, end2-1))
                    break

        for seed in mapped_seeds:
            temp_list.append(mapped_seeds[seed])
        for seed in not_mapped_seeds:
            temp_list.append(seed)
        seeds_list = temp_list
        i += 2
    return min([seed.start for seed in seeds_list])


# def find_lowest_location(input_list):
#     seeds_list = [int(number) for number in input_list[0][7:].split(' ')]
#     print(seeds_list)
#     i = 3
#     while i < len(input_list):
#         maps = list()
#         while i < len(input_list) and (input_list[i] != ""):
#             maps.append(list([int(number) for number in input_list[i].split(' ')]))
#             i += 1
#         mapped_seeds = {}
#         temp_list = list()
#
#         seed_ind = 0
#         while seed_ind < len(seeds_list):
#             a = seeds_list[seed_ind]
#             b = seeds_list[seed_ind + 1]
#             seed_range = range(a, a + b)
#             for seed in seed_range:
#                 for map_line in maps:
#                     [dest_start, source_start, range_len] = map_line
#                     if seed in range(source_start, source_start + range_len):
#                         mapped_seeds[seed] = seed + (dest_start - source_start)
#                         break
#             seed_ind += 2
#
#         seed_ind = 0
#         while seed_ind < len(seeds_list):
#             a = seeds_list[seed_ind]
#             b = seeds_list[seed_ind + 1]
#             seed_range = range(a, a + b)
#             for seed in seed_range:
#                 temp_list.append(mapped_seeds[seed] if seed in mapped_seeds else seed)
#             seed_ind += 2
#
#         seeds_list = temp_list
#         i += 2
#     return min(seeds_list)


def main():
    range1 = (1, 5)
    range2 = (3, 7)
    intersection, differences = find_intersection_and_difference(range1, range2)

    print("Intersection:", intersection)
    print("Non-intersecting Ranges:", differences)
    input_file_path = "/Users/Maksym_Kostynskyi/Code/playground/advent_of_code_2023_cpp/advent_of_code_2023_cpp/input.txt"  # Change this to your actual file path
    try:
        with open(input_file_path, 'r') as inputFile:
            input_list = inputFile.read().splitlines()

        result = find_lowest_location(input_list)
        print(f"The result is: {result}")
    except FileNotFoundError:
        print("Error, cannot open input file")


if __name__ == "__main__":
    main()
