# Each subdirectory must supply rules for building sources it contributes

$(OBJDIR)/%.o: $(SRCDIR)/xml/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	@echo $(CPP) $(CFLAGS) -o$@ $<
	@$(CPP) $(CFLAGS) -o$@ $<
	@echo 'Finished building: $<'
	@echo ' '
