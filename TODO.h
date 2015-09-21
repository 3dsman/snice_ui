widgets:
    file_selector
    timeline
dialogs:
    filepicker
    ajouter alertbox
autre:
	file system posix -> revoir toutes les fonctions
	eliminer la classe list de UI_base
	passer width et height en unsigned
	dans le set content de la classe array, gerer le remplacement (supprimer l'ancien child)
	file_selector -> creer une classe array capable d'afficher des tableau de data et l'utiliser dans le slided_panel du file selector
    rentrer la classe "option" comme sous classe de "submenu"
    creer une classe font derivée de UI_image
	mettre en place un systeme de placers (pour positionner automatiquement des elements de l'interface, les redimenssioner,...)
    integrer les viewport array
    gerer les textures de curseur dans les viewports
    UI_window -> ajouter un resize a la souris?
    choix de la couleur de l'interface
    infobulles?
widgets:
	
    colorband:gerer l'affichage des interpolations avec une texture (interpolation vertex color pour le moment)
	array -> pouvoir setter des styles par cases (selection, couleur, contour, editabilité du texte,...)
    slider -> edition au clavier
    textbox -> autosize? modifier le curseur pour avoir une ligne opengl?; copier/coller?

