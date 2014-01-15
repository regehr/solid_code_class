/^Testing/ { 
    NAME = gensub(/Testing: \.\/([^/]*)\/triangle/, "\\1", $0); 
}

/^[0-9]+/ {
    names[NAME] = NAME
    results[NAME, "pass"] += $1;
    results[NAME, "fail"] += $4;
}

END {
    for (name in names) {
        printf "%d %d %s\n", results[name, "pass"], results[name, "fail"], name;
    }
}
