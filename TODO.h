widgets:
    W_array -> gerer des tailles relatives ou absolues de colonnes/lignes .
    W_array -> ajouter une option de bordure aux cells
    W_fileSelector-> ajouter la coloration des selections
    W_menu -> corriger les sous menu qui s'affichent en dessous des autres elements
    W_menu -> revoir le systeme de callback? utiliser un callback qui retourne le menu en caller et un pointeur supplementaire sur le submenu?
    W_droplist -> a creer
    W_colorband -> gerer l'affichage des interpolations avec une texture (interpolation vertex color pour le moment)
    W_slider -> edition au clavier
    W_textBox -> autosize? modifier le curseur pour avoir une ligne opengl?; copier/coller?
    W_label -> gerer les .. finaux en fonction de la taille
    W_colorDisplay -> creation d'un colorpicker au clic?
    W_timeline -> a integrer
    W_menuBar -> a creer
dialogs:
	filePicker-> gerer le callback des extensions...
    filePicker-> gerer les noms des fichiers selectionnés dans le textbox
    filePicker-> gerer les chemins de repertoires (boutons? menus? textbox?)
    filePicker-> ajouter une ligne de description en haut de l'array (name, date,...)
    alertbox -> a creer
autre:
    utiliser la classe color partout
	file system posix -> revoir toutes les fonctions
	gestion de la molette (notament dans les slided_panel et les sliders)
    rentrer la classe "option" comme sous classe de "submenu"
    creer une classe font derivée de UI_image
	mettre en place un systeme de placers (pour positionner automatiquement des elements de l'interface, les redimenssioner,...)
    integrer les viewport array
    gerer les textures de curseur dans les viewports
    UI_window -> ajouter un resize a la souris? (lié a la disponibilité de pacers)
    infobulles?

