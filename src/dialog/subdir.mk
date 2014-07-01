# Each subdirectory must supply rules for building sources it contributes

$(OBJDIR)/%.o: $(SRCDIR)/dialog/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	@echo $(CPP) $(CFLAGS) -o$@ $<
	@$(CPP) $(CFLAGS) -o$@ $<
#	echo -n $(@:%.o=%.d) $(dir $@) > $(@:%.o=%.d) && \
#	$(CPP) -MM -MG -P -w -I. -Iglfw -Ixml -O0 -g -c -fmessage-length=0  $< >> $(@:%.o=%.d)
	@echo 'Finished building: $<'
	@echo ' '
