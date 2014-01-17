BEGIN {
    system("date");
}

/^Testing/ { 
    NAME = gensub(/Testing: \.\/([^/]*)\/triangle/, "\\1", $0); 
}

/^[0-9]+/ {
    names[NAME] = NAME
    results[NAME, "pass"] += $1;
    results[NAME, "fail"] += $4;
}

END {
    printf "\npassed:\n\n"
    for (name in names) {
        if (results[name, "fail"] > 0) {
            failed[name] = name
        } else  {
            print name
        }
    }
    printf "\nfailed: (results can be found at: https://gist.github.com/Joshkunz/8429888 )\n\n"
    for (name in failed) {
        print name
    }
}
