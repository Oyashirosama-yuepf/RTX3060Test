function _holobag() {
    COMPREPLY=()
    local cur=${COMP_WORDS[COMP_CWORD]};
    local com=${COMP_WORDS[COMP_CWORD-1]};
    case $com in
    'holobag')
        COMPREPLY=($(compgen -W 'record play info filter' -- $cur))
        ;;
    'record')
        local pro=($(compgen -W '-h -v -m -n -c -O ' -- $cur))
        if [[ ${cur} == -* ]] ; then
            COMPREPLY=( $(compgen -W '${pro[@]}' -- ${cur}) )
        fi
        ;;
    'play')
        local pro=($(compgen -W '-h -v -m -n -c -i -s -r' -- $cur))
        if [[ ${cur} == -* ]] ; then
            COMPREPLY=($(compgen -W '${pro[@]}' -- $cur))
        fi
        ;;
    'info')
        local pro=($(compgen -W '-h -v -m' -- $cur))
        if [[ ${cur} == -* ]] ; then
            COMPREPLY=($(compgen -W '${pro[@]}' -- $cur))
        else
            COMPREPLY=( $(compgen -o default -- ${cur}) )
        fi
        ;;
    'filter')
        local pro=($(compgen -W '-h -v -m -i -o -s -e -t' -- $cur))
        if [[ ${cur} == -* ]] ; then
            COMPREPLY=($(compgen -W '${pro[@]}' -- $cur))
        else
            COMPREPLY=( $(compgen -o default -- ${cur}) )
        fi
        ;;
    '-i')
        COMPREPLY=( $(compgen -o default -- ${cur}) )
        ;;
    '-o')
        COMPREPLY=( $(compgen -o default -- ${cur}) )
        ;;
    esac
    return 0
}

complete -F _holobag holobag