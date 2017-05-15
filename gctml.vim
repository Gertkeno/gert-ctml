" vim syntax file
" gert-ctml

if exists("b:current_syntax")
	finish
endif

syn match tagStart '\(^\|\s\)\[\w\+'
syn match tagEnd '\])\|\]'

let b:current_syntax = "gctml"

hi def link tagStart Type
hi def link tagEnd Type
