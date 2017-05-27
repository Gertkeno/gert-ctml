" vim syntax file
" gert-ctml

if exists("b:current_syntax")
	finish
endif

syn match tagStart '\v(^|\s)\[(\w|\d)+(\{.{-}\})=\S*' contains=tagQuickAttrib,tagCustomAttrib,tagLinkAttrib
syn match tagCustomAttrib '\v\{.{-}\}' contained
syn match tagQuickAttrib '\v(\.|\#)(\w|\d|-)+' contained
syn match tagLinkAttrib '\v(\$|\@)\S+' contained
syn match tagEnd '\v\\=(]\)|])' contains=escaped
syn match escaped '\\.'
syn match tagComment '\v(\*.{-}\*)|(\*.*)'
syn match characterCode '&.\{-};'

let b:current_syntax = "gctml"

hi def link tagStart Constant
hi def link tagEnd Constant
hi def link tagQuickAttrib Comment
hi def link tagCustomAttrib Comment
hi def link tagLinkAttrib Comment
hi def link escaped Normal
hi def link tagComment CursorColumn
hi def link characterCode Special
