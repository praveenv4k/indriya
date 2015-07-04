__author__ = 'GVlab'

import csv

languages = ['C#','C++','Python','Javascript','Others']
langout = ['C\#','C++','Python','Javascript (JS)','Others']
langpie = ['C\#','C++','Python','JS','Others']
counts = [0,0,0,0,0]
others = 0

def check_exist(csvLang):
    for lang in languages:
        if lang in csvLang:
            return lang
    return ''

def csv_reader(file_obj):
    reader = csv.reader(file_obj)
    i=0
    for row in reader:
        #print(" ".join(row))
        #if i>2:
        #    break
        if i>0:
            #print row[1]

            lang = check_exist(row[1])
            if lang is not '':
                #print row[1]
                index = languages.index(lang)
                counts[index] = counts[index] + int(row[4])
                continue
            else:
                index = languages.index('Others')
                counts[index] = counts[index] + int(row[4])
                continue

        i=i+1

if __name__ == "__main__":
    csv_path = "cloc_code_statistics.csv"
    with open(csv_path, "rb") as f_obj:
        csv_reader(f_obj)

    print languages
    print counts

    total = sum(counts)

    percentage = ''

    code_table = 'Language & Lines of code \\\ \hline \n'
    comma = 0
    for lang in languages:
        if comma is 1:
            percentage = percentage + ','
        index = languages.index(lang)
        code_table = code_table + langout[index] + ' & ' + str(counts[index]) + '\\\ \n'
        p = float(counts[index])/total
        percentage = percentage + str(round(p*100,2)) + '/' + langpie[index]
        comma = 1
    code_table = code_table + '\hline \n Total' + ' & ' + str(total) + '\\\ \hline \n'
    print code_table
    print percentage