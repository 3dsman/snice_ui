.PHONY: clean All

All:
	@echo "----------Building project:[ snice_ui - linux ]----------"
	@$(MAKE) -f  "snice_ui.mk"
clean:
	@echo "----------Cleaning project:[ snice_ui - linux ]----------"
	@$(MAKE) -f  "snice_ui.mk" clean
