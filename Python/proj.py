import json
collection=json.load(open("dictionary.json"))

def search(word):
    word=word.lower()
    from difflib import get_close_matches
    if word in collection:
        return(collection[word])
    elif len(get_close_matches(word,collection.keys()))>0:
        m={}
        q=get_close_matches(word,collection.keys())
        for i in range(len(q)+1):
                if i<len(q):
                    m[i+1]=q[i]
                    print(i+1,". ",q[i])
                else:
                    strs="None of these"
                    m[i+1]=strs
                    print(i+1,". ",strs)
        choice=int(input("enter one of the above choices"))
        if choice<len(q):
            return(m[choice],collection[m[choice]])
        else:
            import webbrowser
            search_terms = [word]
            for term in search_terms:
                url = "https://www.google.com.tr/search?q={}".format(term)
                webbrowser.open_new_tab(url)
            return("You are being redirected to Google. Please wait.......")
    else:
        print("please enter the word")

def translate(word):
    import goslate
    gs=goslate.Goslate()
    m={'Hindi':"hi",'Tamil':"ta",'Telegu':"te",'French':"fr"}
    g=list(m.keys())
    for i in range(len(g)+1):
        if i<len(g):
            print(i+1,". ",g[i])
        else:
            print(i+1,". ","None of These")
    choice=int(input("select one of the above"))
    if choice<=len(g):
        return(gs.translate(word,m[g[choice-1]]))
    else:
        return("Sorry, we are working on including more languages.")
    
def thesaurus(word):
    from py_thesaurus import Thesaurus
    new_instance = Thesaurus(word)
    return(new_instance.get_synonym())
    
def choice():
    choice=["search","translate","thesaurus"]
    schoice=[search,translate,thesaurus]
    mychoice=0
    while(mychoice!=4):
        for i in range(len(choice)+1):
            if i<len(choice):
                print(i+1,". ",choice[i])     
            else:
                print(i+1,". ","Exit")
        mychoice=int(input("enter one of these"))             
        if mychoice<=len(choice):
            words=input("enter word:")
            output=schoice[mychoice-1](words)
            print(output)
        else:
            exit()    
choice()
                 




 

        


