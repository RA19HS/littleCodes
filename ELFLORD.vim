" local syntax file - set colors on a per-machine basis:
" vim: tw=0 ts=4 sw=4
" Vim color file
" Maintainer:	Reza Ahangarpour   $$ based on elflord
" Last Change:	2020 Aug 21

set background=dark
hi clear
if exists("syntax_on")
  syntax reset
endif
let g:colors_name = "elflord"
" see :help cterm-colors
hi Boolean			ctermfg=Gray
hi Character		ctermfg=Gray
hi Conditional		ctermfg=White
hi Comment			ctermfg=DarkCyan
hi Constant			ctermfg=LightRed
hi Debug			ctermfg=DarkMagenta
hi Define			ctermfg=LightBlue
hi Delimiter		ctermfg=DarkMagenta
hi Error			ctermfg=White	ctermbg=Red
hi Exception		ctermfg=Yellow
hi Float			ctermfg=Brown
hi Function			ctermfg=White
hi Identifier		ctermfg=Cyan	cterm=bold
hi Ignore			ctermfg=black
hi Include			ctermfg=White
hi Keyword			ctermbg=Yellow
hi Label			ctermfg=Red
hi Macro			ctermfg=LightBlue
hi Number			ctermfg=Brown
hi Operator			ctermfg=Red
hi PreCondit		ctermfg=LightBlue
hi PreProc			ctermfg=LightBlue
hi Repeat			ctermfg=White
hi SpecialChar		ctermfg=Cyan
hi SpecialComment	ctermfg=DarkMagenta
hi Statement		ctermfg=Yellow
hi StorageClass		ctermfg=LightRed
hi String			ctermfg=Blue
hi Structure		ctermfg=White
hi Tag				ctermfg=DarkMagenta
hi Todo				ctermfg=Black	ctermbg=Yellow
hi Type				ctermfg=LightGreen
hi Typedef			ctermfg=LightRed
